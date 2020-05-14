/*
  Author: Sebastian
  Co-Authors:
*/
import React, {PureComponent} from 'react';
import "./HomePage.css";
import TheFarmPlant from './TheFarmPlant.js'



class HomePage extends PureComponent {
	constructor(props) {
		super(props);
		this.state = {
			user: this.props.currentUser.getUser(),
		};

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


	//render this page depending on user-state
	render() {
		let thisPage = null;
		if (this.state.user) {
			thisPage = (
				<div className="HomePageContainer">
					{this.state.user ? <TheFarmPlant userID={this.state.user.uid}/> : null}
				</div>
			);
		}
		return (
			<div>
				{thisPage}
			</div>
		);
	}
}

export default HomePage;
