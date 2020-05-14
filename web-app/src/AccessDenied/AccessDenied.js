/*
  Author: Max Ryblad
  Co-Authors:
*/
import React, {Component} from "react";
import "./AccessDenied.css";


class AccessDenied extends Component{
	constructor(props) {
		super(props);
    this.state = {
			user: this.props.currentUser.getUser(),
		};
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

	render() {
    var component = null;
    if(this.state.user == null && window.location.pathname !== "/"){
      component = (<div className="AccessDeniedContainer">
				<p>This page does not exist or you need to be logged in to access it<br/>Log in <a href="/">here</a></p>
			</div>);
    }
		return component;
	}
}

export default AccessDenied;
