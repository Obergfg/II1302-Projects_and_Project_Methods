/*
  Author: Sebastian
  Co-Authors:
*/

import React, {Component} from "react";
import "./StartPage.css";

/**
 * This class is the start page for this website.
 * It takes input from user and sends it to the UserAccount component for authentication
 * */
class StartPage extends Component {
	constructor(props) {
		super(props);
		this.state = {
			formName: "signUp",
			activeForm: null,
			helloMsg: "Create an account!",
			switchForm: "log in", 
			email: null,
			password: null,
			user: this.props.currentUser.getUser(),
		};
	}

	// add this as observer for the UserAccount and render the signUp form
	componentDidMount() {
		this.props.currentUser.addObserver(this);
		this.getActiveForm(this.state.formName);
	}

	//remove this as an observer
	componentWillUnmount() {
		this.props.currentUser.removeObserver(this);
	}

	//called from the observer class
	update() {
		this.setState({
			user: this.props.currentUser.getUser()
		})

	}

	//show the active form (sign up or log in)
	getActiveForm(thisFormName) {
		let form = null;

		switch (thisFormName) {
			case "signUp":
				form = (
					<div className="signupForm">
						<br></br>
						<input type="text" name="email" placeholder="email" onChange={evt => this.setEmail(evt)}></input>
						<br></br>
						<input type="password" placeholder="password" onChange={evt => this.setPassword(evt)}></input>
						<br></br>
						<button onClick={() => this.props.currentUser.createUser(this.state.email, this.state.password)}>Sign up</button>
					</div>
				);
				this.setState({
					activeForm: form,
					helloMsg: "Create an account",
					switchForm: "log in",
				});
				break;
			case "logIn":
				form = (
					<div className="logInForm">
						<br></br>
						<input type="text" name="email" placeholder="email" onChange={evt => this.setEmail(evt)}></input>
						<br></br>
						<input type="password" placeholder="password" onChange={evt => this.setPassword(evt)}></input>
						<br></br>
						<button onClick={() => this.props.currentUser.logInUser(this.state.email, this.state.password)}>Log in</button>
						
					</div>
				);
				this.setState({
					activeForm: form,
					helloMsg: "Welcome back!",
					switchForm: "sign up",
				});
				break;
			default:
				break;

		}
	}

	//event for email input
	setEmail(evt) {
		this.setState({
			email: evt.target.value,
		});
		
	}

	//event for password input
	setPassword(evt) {
		this.setState({
			password: evt.target.value,
		});
	
	}


	/**
	 * Enables users to reset their password
	 */
	resetPassword(){
		if(this.state.email){
			this.props.currentUser.resetPassword(this.state.email)
		}else{
			alert("Type in your email address to reset your password!");
		}
			
	}

	//event handler for switching forms 
	//from login to signup and vice versa
	changeForm = () => {
		switch (this.state.formName) {
			case "signUp":
				this.setState({
					formName: "logIn",	
				});
				this.getActiveForm("logIn");
				break;
			case "logIn":
				this.setState({
					formName: "signUp",
				});
				this.getActiveForm("signUp");
				break;
			default:
				break;
		}
	}

	//render method for login/signup page
	render() {
		if (this.state.user) {
			window.location = '/Home';
		}

		return (
			<div className="StartPageContainer">
				<br></br>
				<div className="StartPageContent">{this.state.helloMsg}</div>
				<div>{this.state.activeForm}</div>
				<div className="testd">
					<button className="switchForm" onClick={this.changeForm}>{this.state.switchForm}</button>
					<br></br>
					<button onClick={() => {this.resetPassword()}}>Reset password</button>
				</div>
			</div>
		);
	}
}

export default StartPage;