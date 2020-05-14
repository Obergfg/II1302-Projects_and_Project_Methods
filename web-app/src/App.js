/*
  Author: Sebastian
  Co-Authors: Homam
*/
import React, { Component } from "react";
import { Route } from "react-router-dom";
import Header from './Header/Header';
import StartPage from './StartPage/StartPage';
import HomePage from './HomePage/HomePage';
import WeatherOverview from './WeatherOverview/WeatherOverview';
import WeatherDetails from './WeatherDetails/WeatherDetails';
import PlantDetails from './PlantDetails/PlantDetails';
import AccessDenied from './AccessDenied/AccessDenied';
import './App.css';
import user from './UserAccount/UserAccount';


class App extends Component {

	render() {
		return (
			<div className="App">
				<header className="App-header">
					<Header currentUser={user}/>
				</header>

				<Route
					exact path="/"
					render={() => <StartPage currentUser={user}/>}
				/>
				<Route
					exact path="/Home"
					render={() => <HomePage currentUser={user} />}
				/>
				<Route
					exact path="/WeatherOverview"
					render={() => <WeatherOverview currentUser={user} />}
				/>
				<Route
					exact path="/WeatherDetails"
					render={() => <WeatherDetails currentUser={user} />}
				/>
				<Route
					exact path="/PlantDetails"
					render={() => <PlantDetails currentUser={user} />}
				/>

				<AccessDenied currentUser={user}/>


			</div>

		);
	}
}

export default App;
