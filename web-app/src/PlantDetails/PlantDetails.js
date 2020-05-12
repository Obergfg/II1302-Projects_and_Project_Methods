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



		  	days : this.determineFiveWeekdays(), 
			dates: this.determineFiveDates(),	
			humidity: "",						
			sun: ""								
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
		
		if(this._isMounted){
            this.intervalID = setTimeout(() => {
                userDB.getHardwareIDFromDB(this.state.user.uid);
				let humidData = userDB.getHumidityHistory();
				let sunData = userDB.getSunHoursHistory();
				this.setState({
					chartData:{
						labels: ["five days ago", "four days ago", "three days ago", "two days ago", "yesterday", "today"],
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
							label:'Sun Hours',
							data:sunData,
							backgroundColor:[
								'rgba(245, 215, 110, 1)',
							]
						}]
					}
				});
            }, 1000);
        }
	}

	determineFiveWeekdays() {
		let d = new Date();	
		let dayNumber = d.getDay();
		let weekday = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
		let arr = [];

		for(let i = 0; i < 5; i++) {
			if((dayNumber - i) < 0) { dayNumber += 7  } //reset to acces elemens in beginning of array. out of bound otherwise
			arr[4-i] = weekday[dayNumber - i];
		}
		return arr;
	}


	determineFiveDates() {
		
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
	
	render() {

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
			itemsHum.push(<td key={i}>{this.state.humidity[i]}</td>)
			itemsSun.push(<td key={i}>{this.state.sun[i]}</td>)
		}
	
		return (
			<div className="PlantDetailsContainer">
				<Chart title="Humidity level" chartData={this.state.chartData} legendPosition="bottom"/>
				<Chart title="Sun hours" chartData={this.state.chartDataSun} legendPosition="bottom"/>
				<div className="Rectangle">
				<h1>Details for the last five days</h1>
					<div className="Table">
						<table>
							<tbody>
								<tr className="Column1">
									<td>Plant Details</td>
									{itemsDays}
									
								</tr>
								<tr className="Row1">
									<td>Humidity</td>
									{itemsHum}
									
								</tr>
								<tr className="Row1">
									<td>Amount of sunlight</td>
									{itemsSun}
								</tr>
							</tbody>
						</table>
					</div>
				</div>
			</div>
		);
	}
	
}

export default PlantDetails;