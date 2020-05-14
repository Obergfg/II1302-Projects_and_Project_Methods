/*
  Author: Sebastian
  Co-Authors:
  Code Properties: Create and maintains the user database.
    See the databse structure at https://app.lucidchart.com/documents/edit/9f482f4d-c28a-4036-9ee2-1c2dcee3de70/jxzR.Zoe1DcX
*/
import {PureComponent} from 'react';
import * as firebase from 'firebase';

class UserDB extends PureComponent{
    constructor(props){
        super(props);
        this._isMounted = false;
        this.uid = null;
        this.hum = 'loading...';
        this.name = "-";
        this.desc = "-";
        this.hardware = "-";
        this.actualHum = "0";
        this.humidArr = [];    //stores the data now showing on chart
        this.nextHumidArr = [];    //acts as a buffer, stores next set of data used in chart 
        this.sunArr = [];    //stores the data now showing on chart
        this.nextSunArr = [];   //acts as a buffer, stores next set of data used in chart 
        this.intervalIDHum = null; //timer for humidityhistory
        this.intervalIDSun = null; //timer for sunHistory
    }


    getPlantDesc(){
        return this.desc;
    }
    getPlantName(){
        return this.name;
    }
    getHum(){
       return this.hum;
    }

    getActualHum(){
        return this.actualHum;
     }

    getHardWareID(){
        return this.hardware;
    }


    /**
     * Creates an empty database for new users
     *
     * @param {firebase user object} user
     */
    createDBForNewUser(user){
        firebase.database().ref("Users")
        .once("value")
          .then(function(snapshot) {
            let children = snapshot.child(user.uid).val(); // {PlantList:"",TheFarmPlant:""}
            if(!children){
                firebase.database().ref('Users/' + user.uid)
                .set({
                    TheFarmPlant: 'empty',
                    HardWareID: '-',
                });

                //adds default starter DB for new users
                firebase.database().ref('Users/' + user.uid + '/TheFarmPlant')
                .once('value')
                .then(function(snapshot){
                    let children = snapshot.child('WantedHumidity').val();

                    if(!children){
                        firebase.database().ref('Users/' + user.uid + '/TheFarmPlant')
                        .set({
                            WantedHumidity: 50,
                            PlantName: "-",
                            PlantDescription: "-",
                        })
                    }
                });
            }
          });
    }

    /**
     * Change the wanted humidity.
     *
     * @param {Integer} newHumidity the new wanted humidity
     * @param {String} userID the ID for a user used to modify the database connected to this user
     */
    changeWantedHumidity(newHumidity, userID){
        firebase.database().ref('Users/' + userID + '/TheFarmPlant')
        .once('value')
        .then(function(snapshot){
            let emptyTree = snapshot.child('TheFarmPlant').val();
            if(!emptyTree){
                firebase.database().ref('Users/' + userID + '/TheFarmPlant')
                .update({
                    WantedHumidity: newHumidity,
                })
            }
        });
    }
    /**
     * Change the name and plant description
     *
     * @param {String} userID the ID for a user used to modify the database connected to this user
     * @param {String} newPlantName the new plant name
     * @param {String} newPlantDescription the new plant description
     */
    setTheFarmPlantInfo(userID, newPlantName, newPlantDescription){
        firebase.database().ref('Users/' + userID + '/TheFarmPlant')
        .once('value')
        .then(function(snapshot){
            let emptyTree = snapshot.child('TheFarmPlant').val();
            if(!emptyTree){
                firebase.database().ref('Users/' + userID + '/TheFarmPlant')
                .update({
                    PlantName: newPlantName,
                    PlantDescription: newPlantDescription,
                })
            }
        });
    }

    /**
     * Updates the user's selected hardwareID in the database.
     * @param {String} userID the ID for a user used to modify the database connected to this user
     * @param {String} hwID the ID of the hardware the user wants to see
     */
    setHardwareID(userID, hwID){
      var ref = firebase.database().ref('Plants/HardwareID' + hwID);
      var val;
      ref.on('value', snap => {
        if(snap.val() == null){           //hardwareID not in DB
          val = "-";
        }
        else{                             //hardwareID in DB
          val = hwID;
        }
        firebase.database().ref('Users/' + userID + '/HardWareID')
        .once('value')
        .then(function(snapshot){
          firebase.database().ref('Users/' + userID)
          .update({
              HardWareID: val,
          })
        });
      });
    }

    /**
     * Get the wanted humidity from the database
     * @param {String} userID the ID for a user used to modify the database connected to this user
     */
    getWantedHumidity(userID){
        //get the wanted humidity from DB
        let ref = firebase.database().ref('Users/' + userID + '/TheFarmPlant');
        let child = ref.child('WantedHumidity');
        child.on('value', snap => {
                this.hum = snap.val();
            
        });
    }

    /**
     * Get the farm plant information from the database
     *
     * @param {String} userID
     */
    getTheFarmPlantInfo(userID){
        let ref = firebase.database().ref('Users/' + userID + '/TheFarmPlant');
        let childFirst = ref.child('PlantName');
        childFirst.on('value', snap => {
            if(snap.val()){
                this.name = snap.val();
            }
         
        });
        let childSecond = ref.child('PlantDescription');
        childSecond.on('value', snap => {
            if(snap.val()){
                this.desc = snap.val();
            }
           
        });
    }

    /**
     * Get the hardware ID connected to this user
     * This  method has to be called before any other methods related to a specific hardware is called.
     * @param {Integer} userID
     */
    getHardwareIDFromDB(userID){
        //get the hardware id
        let ref = firebase.database().ref('Users/' + userID);
        let child = ref.child('HardWareID');
        child.on('value', snap => {

                this.hardware = snap.val();
              
        });
    }

    /**
     * Get the current humidity
     */
    getActualHumidityFromDB(){
        if(this.hardware !== "-"){
            let ref = firebase.database().ref('Plants/HardwareID' + this.hardware);
            let child = ref.child('MoistureLevel').limitToLast(1);

            child.on('value', snap => {
                let a = snap.val();
                this.actualHum = a[Object.keys(a)];
               
            });
        }
    }

    /**
     * Get all information stored about humidity level for a specific hardware
     */
    getHumidityHistory(){
        if(this.hardware !== "-"){
           
            let ref = firebase.database().ref('Plants/HardwareID' + this.hardware);
            let child = ref.child('MoistureLevel');
            let arr = [];

            child.on('value', (snap) => {
            
                Object.keys(snap.val()).map(function (key){
                    arr.push(snap.val()[key]);
                })
            });

            //Make sure that chart still shows values even if method is fetching data from DB
            //Also act as a buffer
            //clears listeners after 3 seconds (gives enough time to use listeners once but not more)
            ////////////////Buffer///////////////////////
            if(arr.flat().length > 0){
                this.nextHumidArr = arr.flat();
                child.off('value');
            }else{
                this.humidArr = this.nextHumidArr;
                this.intervalIDHum = setTimeout(() => {
                    child.off('value');
                }, 4000)
            }
            /////////////////////////////////////////////

            return this.humidArr;
        }
    }

    /**
     * Get all information stored about sun hours for a specific hardware
     */
    getSunHoursHistory(){
        if(this.hardware !== "-"){
            let ref = firebase.database().ref('Plants/HardwareID' + this.hardware);
            let child = ref.child('LightLevel');
            let arr = [];

            child.on('value', snap => {
                Object.keys(snap.val()).map(function (key){
                    arr.push(snap.val()[key]);

                })
            });
            //Make sure that chart still shows values even if method is fetching data from DB
            //Also act as a buffer
            //clears listeners after 3 seconds (gives enough time to use listeners once but not more)
            ////////////////Buffer///////////////////////
            if(arr.flat().length > 0){
                this.nextSunArr = arr.flat();
                child.off('value');
            }else{
                this.sunArr = this.nextSunArr;
                this.intervalIDSun = setTimeout(() => {
                    child.off('value');
                }, 4000)
            }
            /////////////////////////////////////////////

            return this.sunArr;
        }
    }
}

const userDB = new UserDB();
export default userDB;
