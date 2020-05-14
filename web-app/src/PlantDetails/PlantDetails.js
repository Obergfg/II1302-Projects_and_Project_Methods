import React, { Component } from "react";
import "./PlantDetails.css";
import userDB from '../Database/UserDB';
import Chart from './Chart.js';

class PlantDetails extends Component {
	constructor(props){
		super(props);
		this.intervalID = null;
		this._isMounted = false;
		this.state = {
		  	chartData:{},
		 	chartDataSun:{},
		 	user: this.props.currentUser.getUser(),
		 	tableSun: [],
		    tableHum: [],
			days : previousWeekdays(),
			dates: previousDates(),
			humidity: ["", "", "", "", ""],
			sun: ["", "", "", "", ""],
			loadingStatus: "Refresh",
		}
	  }
	//add this as an observer for the user-state
	componentDidMount() {
		this._isMounted = true;
		this.props.currentUser.addObserver(this);

	}

	//remove this as an observer
	componentWillUnmount() {
		clearTimeout(this.intervalID);
		this._isMounted = false;
		this.props.currentUser.removeObserver(this);
	}

	//called from the observed class
	update() {
		this.setState({
			user: this.props.currentUser.getUser()
		});
	}

	componentDidUpdate(){
		clearTimeout(this.intervalID);

		if(this._isMounted && this.state.user){
            this.intervalID = setTimeout(() => {
				this.refreshChartsAndTable(5);
            }, 300000);//1 min
        }
	}

	refreshChartsAndTable(index){

		clearTimeout(this.intervalID);

		if(this._isMounted && this.state.user){
		
            this.intervalID = setTimeout(() => {
                userDB.getHardwareIDFromDB(this.state.user.uid);
				let humidData = userDB.getHumidityHistory();
				let sunData = userDB.getSunHoursHistory();
				this.setState({
					chartData:{
						labels: humidData,
						datasets:[{
							label:'Humidity',
							data:humidData,
							backgroundColor:[
								'rgba(75, 119, 190, 1)',
							]
						}]
					},
					chartDataSun:{
						labels: ["five days ago", "four days ago", "three days ago", "two days ago", "yesterday", "today"],
						datasets:[{
							label:'Light exposure',
							data:sunData,
							backgroundColor:[
								'rgba(245, 215, 110, 1)',
							]
						}]
					},
					tableSun: sunData,
					tableHum: humidData,
					sun: this.arrayFunc(sunData),
					humidity: this.arrayFunc(humidData),
					loadingStatus: "loading...",

				});
				//Brute force buffer
				if(index > 0){
					this.refreshChartsAndTable(index-1);
				}
			}, 1000);

		}
	
		if(index === 0){

			this.setState({
				loadingStatus: "Refresh",
			})
		}
	}

	//Checks that the array is not empty and calls calc Average() to calc the average of each fifth of the array's elements
	arrayFunc (arr) {
		
		if(!(arr == null || arr.length === 0)) {
			let returnArr = [];

			for(let i = 0; i < 5; i++) {
				returnArr[i] = this.calcAverage(arr, i)
			}

			return returnArr;

		}
	}

	//Calculates average of a specific fifth of an array determined by the index received
	calcAverage (arr, index) {
		let fifthOfLength = (Math.floor(arr.length/5))

		let arrLength1;

		let accumulator = 0;
		if(!(index === 0)) {
			arrLength1 = index * fifthOfLength;
			fifthOfLength *= (index+1)
		} else {
			arrLength1 = 0;
		}

		for(let i = arrLength1; i < fifthOfLength; i++) {
			accumulator += arr[i];
		}
		return Math.floor(accumulator/fifthOfLength);
	}

	render() {
		let thisPage = null;
		if (this.state.user) {
			let itemsDays = [];
			let itemsHum = [];
			let itemsSun = [];

			for(let i = 0; i < 5; i++)
			{
				itemsDays.push(<td key={i}>
					{this.state.days[i]}
					<br/>
					{this.state.dates[i]}
				</td>)

				if(!(this.state.sun == null || this.state.sun.length == 0 || this.state.humidity == null || this.state.humidity.length == 0)) {
					itemsHum.push(<td key={i}>{this.state.humidity[i]}</td>)
					itemsSun.push(<td key={i}>{this.state.sun[i]}</td>)
				}
			}
			thisPage = (
				<div className="PlantDetailsContainer">
					<button onClick={()=>{this.refreshChartsAndTable(5)}}>{this.state.loadingStatus}</button>
					<Chart className="humidChart" title="Humidity level" chartData={this.state.chartData} legendPosition="bottom"/>
					<Chart title="Light exposure" chartData={this.state.chartDataSun} legendPosition="bottom"/>

					<div className="Rectangle2">
						<h1>Details for the last five days</h1>
						<div className="Table2">
							<table className = 'BestTable1'>
								<tbody>
									<tr className="Column2">
										<td>Plant Details</td>
										{itemsDays}

									</tr>
									<tr className="Row2">
										<td>Average Humidity</td>
										{itemsHum}

									</tr>
									<tr className="Row2">
										<td>Average Sunlight</td>
										{itemsSun}
									</tr>
								</tbody>
							</table>
						</div>
					</div>
				</div>
			);
		}

		return thisPage;
	}

}

	//Determines todays and the past four weekdays
	function previousWeekdays() {
		let d = new Date();
		let dayNumber = d.getDay();
		let weekday = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
		let arr = [];

		for(let i = 0; i < 5; i++) {
			if((dayNumber - i) < 0) { dayNumber += 7 } //reset to acces elemens in beginning of array. out of bound otherwise
			arr[4-i] = weekday[dayNumber - i];
		}
		return arr;
	}

	//Determines todays and the past four dates
	function previousDates() {
		let arr = [];
		for(let i = 0; i < 5; i++)
		{
			let someDate = new Date();
			someDate.setDate(someDate.getDate() - i);

			let dd = someDate.getDate();
			let mm = someDate.getMonth() + 1;
			let y = someDate.getFullYear();

			if(mm < 10) { mm = "0"+mm }
			if(dd < 10) { dd = "0"+dd }

			let someFormattedDate = y+"-"+mm+"-"+dd

			arr[4-i] = someFormattedDate;
		}
		return arr;
	}

export default PlantDetails;
