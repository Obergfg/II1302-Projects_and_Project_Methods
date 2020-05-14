/*
  Author: Sebastian
  Co-Authors:
*/
import React, {Component} from 'react';
import "./TheFarmPlant.css";
import userDB from '../Database/UserDB';



//show the current THE FARM plant
//show info from DB by using user.id from parent component(the Homepage)
class TheFarmPlant extends Component{
    constructor(props){
        super(props);
        //prevents memory loss
        this._isMounted = false;

        this.intervalID = null;

        this.state = {
            humidity: userDB.getHum(),
            humidityBackground: 'default',
            theFarmButton: "Edit",
            editable: false,
            plantDescription: "-",
            plantName: "-",
            hardwareID: "-",
            hardwareHumidity: "-",
        };
    }

    /**
     * Get humidity, plant name and description from DB when mounted
     */
    componentDidMount(){
        this._isMounted = true;

        userDB.getWantedHumidity(this.props.userID);
        userDB.getHardwareIDFromDB(this.props.userID);
        this.setHumidityBackground();
        this.estimateWhenToWater();
        userDB.getActualHumidityFromDB();
        userDB.getTheFarmPlantInfo(this.props.userID);
        this.setState({
            plantDescription: userDB.getPlantDesc(),
            plantName: userDB.getPlantName(),
            hardwareID: userDB.getHardWareID(),
            hardwareHumidity: userDB.getActualHum(),
        })

    }

    //set mounted as false
    //clear all timers
	componentWillUnmount() {
        this._isMounted = false;
        clearTimeout(this.intervalID);
	}

    /**
     * Get humidity, plant name and description from DB when mounted
     * Start by clearing timers to stop timers "overlaping"
     */
    componentDidUpdate(){
        clearTimeout(this.intervalID);

        if(this.state.humidity === 'loading...' && this._isMounted){
            userDB.getWantedHumidity(this.props.userID);

            setTimeout(() => {
                this.setState({
                    humidity: userDB.getHum(),
                })
            }, 1000);
        }

        if(this._isMounted){
            this.intervalID = setTimeout(() => {
                this.setHumidityBackground();
                this.estimateWhenToWater();
                userDB.getActualHumidityFromDB();
                userDB.getTheFarmPlantInfo(this.props.userID);



                this.setState({
                    plantDescription: userDB.getPlantDesc(),
                    plantName: userDB.getPlantName(),
                    hardwareID: userDB.getHardWareID(),//add
                    hardwareHumidity: userDB.getActualHum()
                })
            }, 1000);
        }
    }

    /**
     * Set/change the background of wanted humidity depending on the level of humidity
     */
    setHumidityBackground(){
        let status = 'default'
        if(this.state.humidity !== 'loading...'){
            status = 'low';

            if(this.state.humidity > 66 ){
                status = 'high';

            }else if(this.state.humidity > 33 ){
                status = 'normal';
            }
        }
        this.setState({
            humidityBackground: 'Humidity-control-' + status,
        })

    }

    /**
     * Estimates if your plant needs water and if hardware is linked to the user.
     */
    estimateWhenToWater(){
        let msg = null;
        if(this.state.hardwareID !== "-" && this.state.hardwareHumidity > 0){
            if(parseInt((this.state.humidity) - parseInt(this.state.hardwareHumidity)) > 0){
                msg = "Your plant needs water!"
            }else{
                msg = "Your plant has plenty of water"
            }
        }else{
          msg = "Connect your hardware to your account";
        }
        this.setWateringMessage(msg);
    }

    setWateringMessage(msg){
      this.setState({
          watering: msg
      });
    }

    /**
     * Enables users to manually type the wanted humidity lvl
     * @param {integer} input the humidity level wanted
     */
    manuallyChangeHumidity(input){
        let newHum = input.target.value;
        if(newHum > 100){
            newHum = 100;
        }else if(newHum < 0){
            newHum = 0;
        }
        this.setState({
            humidity: newHum,
        })
    }

    /**
     * Change humidity level
     *
     * @param {Integer} value either 1 or -1 depending on which button was pressed
     */
    changeHumidity(value){
        let newHum = parseInt(this.state.humidity) + value;
        if(newHum > 100){
            newHum = 100;
        }else if(newHum < 0){
            newHum = 0;
        }
        this.setState({
            humidity: newHum,
        })
    }

    /**
     * Apply the humidity change to the database
     */
    applyHumidityChange(){
        userDB.changeWantedHumidity(this.state.humidity, this.props.userID);
    }

    /**
     * Enables editing of plant name and description
     */
    editTheFarmInfo(){
        if(this.state.theFarmButton === "Edit"){ //start editing
            this.setState({
                editable: true,
                theFarmButton: "Save",
            })
        }else{ //saves edits
            if(!document.getElementById('plantName').innerHTML.replace(/\s/g, "").length | !document.getElementById('theFarmPLantText').innerHTML.replace(/\s/g, "").length){
                console.log(document.getElementById('plantName').innerHTML);
                alert("Name and Description can not be empty");
                if(!document.getElementById('plantName').innerHTML.replace(/\s/g, "").length){
                    document.getElementById('plantName').innerHTML = "-";
                }
                if(!document.getElementById('theFarmPLantText').innerHTML.replace(/\s/g, "").length){
                    document.getElementById('theFarmPLantText').innerHTML = "-";
                }
            }else if(document.getElementById('plantName').innerHTML.length > 20){
                alert("Name can not be more than 20 characters including spaces");
            }else if(document.getElementById('theFarmPLantText').innerHTML.length > 120){
                alert("Description has to be no more than 120 characters including spaces");
            }else{
                document.getElementById('plantName').innerText = document.getElementById('plantName').innerText.trim();
                document.getElementById('theFarmPLantText').innerText = document.getElementById('theFarmPLantText').innerText.trim();
                document.getElementById('hwID').innerText = document.getElementById('hwID').innerText.trim();
                this.setState({
                    editable: false,
                    theFarmButton: "Edit",
                })
                userDB.setHardwareID(this.props.userID, document.getElementById('hwID').innerText)
                userDB.setTheFarmPlantInfo(this.props.userID, document.getElementById('plantName').innerText, document.getElementById('theFarmPLantText').innerText);
            }
        }
    }


    render(){

        return(
            <div className='TheFarmPlant'>
                <div className='TheFarmPlant-Info'>
                    <button onClick={() => {this.editTheFarmInfo()}} id="TheFarmPlant-button">{this.state.theFarmButton}</button>
                    <div>Hardware ID: <span suppressContentEditableWarning={true} id="hwID" contentEditable={this.state.editable}>{this.state.hardwareID}</span></div>
                    <h1 className='TheFarmPlant-header'>Your plant</h1>
                    <div type="text" className='TheFarmPLantText'>Name: <span suppressContentEditableWarning={true} id="plantName" contentEditable={this.state.editable}> {this.state.plantName}</span></div>
                    <div>Note: <span id='theFarmPLantText' suppressContentEditableWarning={true} contentEditable={this.state.editable}>{this.state.plantDescription}</span></div>
                </div>
                <div className='Watering' id='WateringID'>
                    <div className='Water-text'>
                        <h1 className='Watering-header'>Water Status</h1>
                        <h2 className='watering-status-msg'>{this.state.watering}</h2>
                    </div>
                </div>
                <div className={this.state.humidityBackground} id='HumidityID'>
                    <div className='Humidity-background'>
                        <h1 className='Humidity-header'>Wanted watering level</h1>
                        <input type='button' value='-' onClick={() => this.changeHumidity(-1)}></input>
                        <input className='Humidity-input' type='text' value={this.state.humidity} onChange={(evt) => this.manuallyChangeHumidity(evt)}></input>
                        <input type='button' value='+' onClick={() => this.changeHumidity(1)}></input>
                        <button className='Apply-new-hummidity-Btn' onClick={() => this.applyHumidityChange()}>Apply</button>
                    </div>
                </div>
            </div>
        );
    }
}

export default TheFarmPlant;
