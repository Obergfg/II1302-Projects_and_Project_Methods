/*
  Author: Sebastian
  Co-Authors:
*/
import React, {PureComponent} from "react";
import "./Header.css";
import { FaBars } from 'react-icons/fa';


/**
 * Header component for the website
 * Includes title and navbar
 * */
class Header extends PureComponent{
	constructor(props) {
		super(props);
		this.state = {
			user: this.props.currentUser.getUser(),
		}
	}

	//observe the state of the current user
	componentDidMount() {
		this.props.currentUser.addObserver(this);
	}

	//remove this as an observer
	componentWillUnmount() {
		this.props.currentUser.removeObserver(this);
	}

	//called when observer changed
	update() {
		this.setState({
			user: this.props.currentUser.getUser()
		})
	}

	//sign out this user
	logOutThisUser() {
		this.props.currentUser.logOutUser();
	}

	/**
	 * hides or shows nav-bar (used for mobile view)
	 * Hide pictures when mobile navbar is present
	 */
	hideOrShowBar(){
		if(document.querySelector('.active-navMenu')){
			document.querySelector('.active-navMenu').className = null;
		}else{
			document.getElementById('navbar').classList.add('active-navMenu');
		}
	}

	/**
	 * Checks what navbar button is active
	 * by comparing the button name with the current url-string. If home page is mounted then home button should be active.
	 * Active button has black background
	 * @param {String} evt is the button that wants to know it is active or not
	 */
	isItActive(evt){
		if(evt === window.location.href.split('/').pop()){
			return 'active-nav'
		}else{
			return 'no';
		}
	}

	render() {
		let thisPage = null;
		if(this.state.user){
			thisPage=(
				<div>
					<nav id='navbar'>
						<ul>
							<li><a className={this.isItActive('Home')} href='/Home'>Home</a></li>
							<li><a className={this.isItActive('PlantDetails')} href='/PlantDetails'>Plant Details</a></li>
							<li><a className={this.isItActive('WeatherOverview')} href='/WeatherOverview'>Weather</a></li>
							<li><a  onClick={() => {this.logOutThisUser()}} href='/'>Sign out</a></li>
						</ul>
					</nav>
					<div onClick={() => {this.hideOrShowBar()}} className='menu-toggle'><FaBars/></div>
				</div>
			);
		}

		return (
			<header className='main-header'>
				<div className='logo' onClick={() => {
          if(this.state.user) {
            window.location.href = 'home'
          }
          else{
            window.location.href = window.location.origin
          }
        }}>The<span>Farm</span></div>
				{thisPage}
			</header>
		);
	}
}

export default Header;
