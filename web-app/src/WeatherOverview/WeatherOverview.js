/*
  Author: Homam Jabir
  Co-Authors:
*/
import React, {Component} from "react";
import "./WeatherOverview.css";
import  {WEATHERAPI, WEATHERAPIKEY}  from "../../src/API/WeatherAPI"

class WeatherOverview extends Component {
	constructor(props) {
		super(props);
		this.state = {
			user: this.props.currentUser.getUser(),
			days : CommingWeekdays(),
			dates : CommingDates(),
			city : "Stockholm",
			temperature: [],
			precipitation: [],
			cloudiness: [],
		};
		this.dayfunc(this.state.city)
	}

	//add this as an observer for the user-state
	componentDidMount() {
		this.props.currentUser.addObserver(this);

	}

	//remove this as an observer
	componentWillUnmount() {
		this.props.currentUser.removeObserver(this);
	}

	//called from the observed class
	update() {
		this.setState({
			user: this.props.currentUser.getUser()
		});
	}

	//API call
	dayfunc() {
		var url = WEATHERAPI + this.state.city + WEATHERAPIKEY;
		fetch(url)
		.then(response =>
		{
			if ( response.status >= 200 && response.status <299) {
				return response.json();
			} else {
				throw Error(response.statusText);
			}

		}).then(data => {
			this.drawWeather(data)
		}).catch((error) => {
			console.log(error);
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

	setTemperature (tempData) { this.setState(prevState => ({temperature: [...prevState.temperature, tempData]}))}

	setPrecipitation (precData) { this.setState(prevState => ({precipitation: [...prevState.precipitation, precData]}))}

	setCloudiness (cloudData) { this.setState(prevState => ({cloudiness: [...prevState.cloudiness, cloudData]}))}

	setCity(evt) { this.setState({city: evt.target.value}) }

	render() {
		let thisPage = null;
		if (this.state.user) {
			let itemsDays = [];
			let itemsTemp = [];
			let itemsPrec = [];
			let itemsCloud = [];

			for(let i = 0; i < 5; i++) {
				let imageURL = "http://openweathermap.org/img/wn/" + this.state.precipitation[i] + "@2x.png"

				itemsDays.push
				(
					<td key={i} ><a href = {'/WeatherDetails?date=' + this.state.dates[i] + '&city=' + this.state.city} id="link" >
						{this.state.days[i]}
						<br/>
						{this.state.dates[i]}
					</a></td>
				)

				itemsTemp.push(<td key={i}>{this.state.temperature[i]}</td>)
				itemsCloud.push(<td key={i}>{this.state.cloudiness[i]}</td>)
				itemsPrec.push(<td key={i}><img id = "WeatherImages11" alt="" src={imageURL}></img></td>)
			}
			thisPage = (
					<div className="WeatherOverviewContainer">
						<div className="Rectangle">Weather Forcast
							<p className="Search">
								City: <input type ="text" value = {this.state.city} onChange={evt => this.setCity(evt)}></input>
								<br/>
								<button onClick={() => this.dayfunc(this.state.city)}>submit</button>
							</p>

							<div className="Table">
								<table className = "BestTable">
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
											<td>Cloudiness</td>
											{itemsCloud}
										</tr>
										<tr className="Row">
											<td>Sky</td>
											{itemsPrec}
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

	//Determines the next five days
	function CommingWeekdays() {
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

	//Determines the next five dates
	function CommingDates() {
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

export default WeatherOverview;
