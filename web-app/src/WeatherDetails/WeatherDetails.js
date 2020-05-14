/*
  Author: Homam Jabir
  Co-Authors:
*/
import React, {Component} from "react";
import "./WeatherDetails.css";
import { WEATHERAPI, WEATHERAPIKEY } from "../../src/API/WeatherAPI"

class WeatherDetails extends Component {
	constructor(props) {
		super(props);
		this.state = {
			user: this.props.currentUser.getUser(),
			url: window.location.href,
			day: "",
			city: "",
			time: [],
			humidity: [],
			precipitation: [],
			wind: [],
			temp: [],
		};
		
		this.apiCall()
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

	//Extracts city name from url and calls API
	apiCall() {
		let pageUrl = this.state.url
		let city = pageUrl.split("city=")
		city = city[1].substring(0, city[1].length)

		var url = WEATHERAPI + city + WEATHERAPIKEY;

		fetch(url)
		.then(response =>
		{
			if ( response.status >= 200 && response.status <299) {
				return response.json();
			} else {
				throw Error(response.statusText);
			}

		}).then(data => {
			this.determineIndex(data, city)
		}).catch((error) => {
			console.log(error);
		});

	}

	//Determines the starting index of data in API response from the date selected
	determineIndex( data, newCity ) {
		let url = this.state.url
		let date = url.split("date=");
		date = date[1].substring(0, 10)

		this.setDate(date)
		if(newCity.includes('%20')) {
			newCity = newCity.replace('%20', ' ')
		}
		this.setCity(newCity)

		let string
		let i;
		for(i = 0; i < 40; i = i + 8) {
			string = (data.list[i].dt_txt).split(" ");
			if(string[0] === date) {
				break;
			}
		}
		//Api returns next day after 22:30 therefore index needs to be reset
		if(i === 40) {
			i = 0

		}

		this.drawWeather(data, i);
	}

	//Extracts the relevant data from the API response with the index from determineIndex()
	drawWeather ( data, index ) {
		let day;
		let time;

		for(let int = index; int < index+8; int++ )
		{
			day = data.list[int];

			if(day.hasOwnProperty('rain')) {
				this.setPrecipitation(day.rain['3h']);
			} else {
				this.setPrecipitation("0")
			}

			time = (data.list[int].dt_txt).split(" ");
			time = time[1].substring(0, 5)

			this.setTime(time);
			this.setWind(day.wind.speed)
			this.setHumidity(day.main.humidity)
			this.setTemperature(Math.round(parseFloat(day.main.temp)-273.15))
		}
	}

	setPrecipitation( precData ) { this.setState(prevState => ({precipitation: [...prevState.precipitation, precData]})) }

	setTime( timeData ) { this.setState(prevState => ({time: [...prevState.time, timeData]})) }

	setWind( windData ) { this.setState(prevState => ({wind: [...prevState.wind, windData]})) }

	setHumidity( humData ) { this.setState(prevState => ({humidity: [...prevState.humidity, humData]})) }

	setTemperature( tempData ) { this.setState(prevState => ({temp: [...prevState.temp, tempData]})) }

	setDate ( dateData ) { this.setState({day: dateData}) }

	setCity ( cityData ) { this.setState({city: cityData}) }

	render() {
		var divArr = [];

		for(let i = 0; i < 8; i++) {
			divArr.push(
				<>
					<td>{this.state.time[i]}</td>
					<td>{this.state.temp[i]}</td>
					<td>{this.state.humidity[i]}</td>
					<td>{this.state.wind[i]}</td>
					<td>{this.state.precipitation[i]}</td>
				</>
			)
		}

		let thisPage = null;
		if(this.state.user){
			thisPage = (<div className="WeatherDetailsContainer">
				<div className="Rectangle1">Weather Details for {this.state.city}, {this.state.day} and the following 24 hours

						<div className="Table1">
							<table>
								<tbody>
									<tr className="Column1">
										<td></td>
										<td>Temperature <br/> (°C)</td>
										<td>Humidity <br/> (%)</td>
										<td>Wind speed <br/> (m/s)</td>
										<td>Precipitation <br/> (mm)</td>
									</tr>
									<tr className="Row1">
										{divArr[0]}
									</tr>
									<tr className="Row1">
										{divArr[1]}
									</tr>
									<tr className="Row1">
										{divArr[2]}
									</tr>
									<tr className="Row1">
										{divArr[3]}
									</tr>
									<tr className="Row1">
										{divArr[4]}
									</tr>
									<tr className="Row1">
										{divArr[5]}
									</tr>
									<tr className="Row1">
										{divArr[6]}
									</tr>
									<tr className="Row1">
										{divArr[7]}
									</tr>
									
								</tbody>
							</table>

							<button className="button1"><a href='/WeatherOverview'>Return</a></button>
						</div>

					
				</div>
			</div>);
		}
		return thisPage;
	}
}

export default WeatherDetails;
