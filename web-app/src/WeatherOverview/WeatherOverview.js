import React, {Component} from "react";
import "./WeatherOverview.css";

const WEATHERAPI = 'https://api.openweathermap.org/data/2.5/forecast?q=';
const WEATHERAPIKEY = '&appid=c8e65a4f40a9f86173cf5e60e03219c8';

class WeatherOverview extends Component {
	constructor(props) {
		super(props);
		this.state = {
			days : this.determineFiveWeekdays(),
			dates : this.determineFiveDates(),
			datedate: "",
			city : "Stockholm",
			temperature: [],
			precipitation: [],
			cloudiness: [],
		};
		this.drawWeather = this.drawWeather.bind(this);
	}

	//Determines the day of the week
	determineFiveWeekdays() {
		let d = new Date();	
		let dayNumber = d.getDay();
		let weekday = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
		let arr = [];

		for(let i = 0; i < 5; i++) {
			if((dayNumber + i) > 6) { dayNumber = (-i) } //reset to acces elemens in beginning of array. out of bound otherwise
			arr[i] = weekday[dayNumber + i];
		}
		return arr;
	}

	determineFiveDates() {
		
		let arr = [];
		for(let i = 0; i < 5; i++)
		{
			let someDate = new Date();
			someDate.setDate(someDate.getDate() + i); 

			let dd = someDate.getDate();
			let mm = someDate.getMonth() + 1;
			let y = someDate.getFullYear();

			if(mm < 10) { mm = "0"+mm }
			if(dd < 10) { dd = "0"+dd }
			
			let someFormattedDate = y+"-"+mm+"-"+dd

			arr[i] = someFormattedDate;
		}
		return arr;
	}
	
	//API call
	dayfunc(city) {
		var url = WEATHERAPI + this.state.city + WEATHERAPIKEY;
		fetch(url)
		.then(response =>
		{
			return response.json();
		}).then(data => {
			console.log(data)
			this.drawWeather(data);
		});
	}

	//Extracts data from API response
	drawWeather( d ) {
		this.setState({temperature: []});
		this.setState({precipitation: []});
		this.setState({cloudiness: []});
		this.setState({weatherData: d})

		let temperatureId;

		for(let i = 0; i < 40; i=i+8)
		{
			temperatureId = d.list[i].weather[0].icon;
			

			this.setTemperature(Math.round(parseFloat(d.list[i].main.temp)-273.15));
			this.setPrecipitation(temperatureId);
			
			this.setCloudiness((d.list[i].weather[0].description));
			
		}
	}
	//pushes data to state array
	setTemperature (data) { this.setState(prevState => ({temperature: [...prevState.temperature, data]}))}

	setPrecipitation (data) { this.setState(prevState => ({precipitation: [...prevState.precipitation, data]}))}

	setCloudiness (data) { this.setState(prevState => ({cloudiness: [...prevState.cloudiness, data]}))}

	setCity(evt) { this.setState({city: evt.target.value}) }

	changePage(date) {
		/*history.push({
			pathname: '/WeatherDetails',
			search: '?date=' + date
		})*/
		console.log(date)
	}
	
	render() {
		let itemsDays = [];
		let itemsTemp = [];
		let itemsPrec = [];
		let itemsCloud = [];
		
		for(let i = 0; i < 5; i++) {
			let imageURL = "http://openweathermap.org/img/wn/" + this.state.precipitation[i] + "@2x.png"

			itemsDays.push(<td key={i} ><a href = '/WeatherDetails' id="link" onClick={() => this.changePage( this.state.dates[i] )}>
				{this.state.days[i]}
				<br/>
				{this.state.dates[i]}
			</a></td>)

			itemsTemp.push(<td key={i}>{this.state.temperature[i]}</td>)
			itemsCloud.push(<td key={i}>{this.state.cloudiness[i]}</td>)
			itemsPrec.push(<td key={i}><img id = "WeatherImages" alt="" src={imageURL}></img></td>)
		}

		return (
				<div className="WeatherOverviewContainer">
					<div className="WeatherOverviewContent">WeatherOverview Content here!</div>
					<div className="Rectangle">Weather Forcast
						<p>
							City: <input type ="text" value = {this.state.city} onChange={evt => this.setCity(evt)}></input>
							<br/>
							<button onClick={() => this.dayfunc(this.state.city)}>submit</button>
						</p>
						<div className="Table">
							<table>
								<tbody>
									<tr className="Column">
										<td>Forecast</td>
										{itemsDays}
									</tr>
									<tr className="Row">
										<td>Temperature</td>
										{itemsTemp}
									</tr>
									<tr className="Row">
										<td>Sky</td>
										{itemsPrec}
									</tr>
									<tr className="Row">
										<td>Cloudiness</td>
										{itemsCloud}
									</tr>
								</tbody>
							</table>
						</div>
					</div>

				</div>
		);
	}
}



export default WeatherOverview;