/*
  Author: Sebastian
  Co-Authors:
*/
import * as firebase from 'firebase';
import Observable from './Observable';
import CONFIG from '../Database/configFirebase';
import UserDB from '../Database/UserDB';

/**
 * Handles the user authentication
 */
class UserAccount extends Observable {
	constructor(props) {
		
		super(props);
		firebase.initializeApp(CONFIG);
		firebase.auth();
		this.user = this.authListener();
	}

	getUser() {
		return this.user;
	}

	/**
	 * Creates user using firebase.auth
	 * (ends with logging out the user)
	 * 
	 * catches errors about signUp
	 * 
	 * @param {any} email the email as a string
	 * @param {any} password the password as a string
	 */
	createUser(email, password) {
		if (email && password !== null) {
			firebase.auth().createUserWithEmailAndPassword(email, password)
				.then(() => {
					firebase.auth().signOut();
				})
				.catch((err) =>{
					alert(err.message);
				})
		}
	}

	/**
	 * Handles log in for the user
	 * 
	 * @param {string} email the email
	 * @param {string} password the password
	 */
	logInUser(email, password) {
		firebase.auth().signInWithEmailAndPassword(email, password)
			.then((user) => {
				if(!user){
					this.logOutUser();
				}else if(user && user.emailVerified){
					this.authListener();
				}
			})
			.catch((err) => {
				alert(err.message);
			});

	}

	/**
	 * Loggs out the user
	 * */
	logOutUser() {
		firebase.auth().signOut()
			.catch((err) => {
				alert(err.message);
			})
			this.user = null;
			this.authListener();
	}

	/**
	 * Sends email reset link to an user email
	 * @param {String} email address to send reset password link to
	 */
	resetPassword(email){
		firebase.auth().sendPasswordResetEmail(email)
			.catch((err) => {
				alert(err.message);
			})
		alert("To reset your password follow the steps sent to your email address");
	}

	/**
	 * 
	 * This method calls everytime the user-state changes (logIn/signOut)
	 * */
	authListener() {
		firebase.auth().onAuthStateChanged((user) => {
			if(user){
				if(user.emailVerified){
					this.user = firebase.auth().currentUser;
					UserDB.createDBForNewUser(this.user);
					//check if user has database otherwice create a start up DB
					// use userDB.createDBForNewUsers(firebase.auth().currentUser.uid);
					//or observer from DB looking at this (look at other examples)
					this.notifyObservers();
				}else{
					alert("Please verify your email");
					user.sendEmailVerification();
					firebase.auth().signOut();
				}
			}else{
				this.notifyObservers();
			}									
		});
	}
}
const user = new UserAccount();
export default user;

