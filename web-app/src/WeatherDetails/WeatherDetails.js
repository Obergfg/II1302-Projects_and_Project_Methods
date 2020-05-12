import React, {Component} from "react";
import "./WeatherDetails.css";

const WEATHERAPI = 'https://api.openweathermap.org/data/2.5/forecast?q=';
const WEATHERAPIKEY = '&appid=c8e65a4f40a9f86173cf5e60e03219c8';


class WeatherDetails extends Component {
	constructor() {
		super();
		
		this.state = {
			//func: this.dayfunc("stockholm"),
			date: "",
			time: [],
			humidity: [],
			precipitation: [],
			wind: [],
			tempMin: [],
			tempMax: []
		};
	}

	dayfunc(city) {
		var url = WEATHERAPI + city + WEATHERAPIKEY;
		fetch(url)
		.then(response =>
		{
			return response.json();
		}).then(data => {
			console.log(data)
			this.drawWeather1(data);
		});
	}

	drawWeather1 ( data ) {
		var date = "2020-05-04"
		//console.log(this.props.location.datedate)
		this.setState({date: date})
		let string
		let i;
		for(i = 0; i < 40; i = i + 8) {
			string = (data.list[i].dt_txt).split(" ");
			if(string[0] == date) {
				console.log(string[1])
				break;
			}
		}
		let day;
		let time;
		
		for(let int = i; int < i+3; int++ )
		{	
			console.log(int)
			day = data.list[int];
			if(day.hasOwnProperty('rain')) {
				this.setState(prevState => ({precipitation: [...prevState.precipitation, day.rain['3h']]}))
			} else {
				this.setState(prevState => ({precipitation: [...prevState.precipitation, "0"]}))
			}

			time = (data.list[int].dt_txt).split(" ");
		
			this.setState(prevState => ({time: [...prevState.time, time[1]]}))
			this.setState(prevState => ({humidity: [...prevState.humidity, day.main.humidity]}))
			this.setState(prevState => ({wind: [...prevState.wind, day.wind.speed]}))
			this.setState(prevState => ({tempMin: [...prevState.tempMin, Math.round(parseFloat(day.main.temp_min)-273.15)]}))
			this.setState(prevState => ({tempMax: [...prevState.tempMax, Math.round(parseFloat(day.main.temp_max)-273.15)]}))
		}

	}

	render() {
		var divArr = [];

		for(let i = 0; i < 3; i++) {
			divArr.push(	
				<div>
					<div className="RectangleMini pos1">Temp Mini (°C): {this.state.tempMin[i]}</div>
					<div className="RectangleMini pos2">Temp Max (°C): {this.state.tempMax[i]}</div>

					<div className="RectangleSmall pos3">Humidity (%): {this.state.humidity[i]}</div>
					<div className="RectangleSmall pos4">Wind Speed (m/sec): {this.state.wind[i]}</div>
					<div className="RectangleSmall pos5">Precipitation (mm): {this.state.precipitation[i]}</div>
				</div>
			)
		}

		return (
			<div className="WeatherDetailsContainer">
				<div className="WeatherDetailsContent">WeatherDetails Content here!</div>

				<div className="SummaryContainer">
					<div className="Rectangle11">Weather Details for {this.state.date}
						<p1 className="DateInfo"></p1>

						<div className="Rectangle22 hem1">Summary for {this.state.time[0]}
							{divArr[0]}
						</div>

						<div className="Rectangle22 hem2">Summary for {this.state.time[1]}
							{divArr[1]}
						</div>

						<div className="Rectangle22 hem3">Summary for {this.state.time[2]}
							{divArr[2]}
						</div>

						<button id="button"><a href='/WeatherOverview'>Return</a></button>
					</div>
				</div>
			</div>
		);
	}
}

export default WeatherDetails;