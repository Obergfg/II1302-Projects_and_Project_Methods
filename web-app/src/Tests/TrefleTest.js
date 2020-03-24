import React, { Component } from "react";

/*
  Author: Max
  Co-Authors:
  Date of creation: 20-03-24
  Date of update: 20-03-24
  Code Properties: Component made to test the Trefle API.
*/
class TrefleTest extends Component {
  constructor(props){
    super(props);

    this.state = {
      searchPhrase: "",
      results: <p>Placeholder for Trefle API test...</p>,
    };

    this.handleChange = this.handleChange.bind(this);
    this.searchPlant = this.searchPlant.bind(this);
    this.processResponse = this.processResponse.bind(this);

    console.log(this);
  }

  /*
    Updates variables to match search box's value when updated.
  */
  handleChange(e) {
    this.setState({
      "searchPhrase": e.target.value
    })
  }

  /*
    Function that fetches and returns data about the plant searched for.

    @return JSX object of fetched data.
  */
  searchPlant(){
    /*
    //Denna koden funkar säkert inte, har inte kunnat testa så det är bara ett förslag för anropet.
    fetch("https://trefle.io/api/species/{this.state.searchPhrase}?token={TREFLETOKEN}")
    .then(this.processResponse)
    ...
    */
    this.setState({
      "results": <div className="results"><p>Plant for {this.state.searchPhrase} result...</p></div>
    })
  }

  /*
    Function that filters out unncessary information from fetch request
    and returns a JSX object with the wanted information.

    @param json received from api fetch.
    @return JSX object with the necessary information.
  */
  processResponse(json){

  }

  render() {
    return (
      <div className="TreffleTest">
        <input value={this.state.searchPhrase} onChange={this.handleChange} name="searchPhrase" placehold="Search"></input>
        <button type="submit" onClick={this.searchPlant}>Search</button>
        {this.state.results}

      </div>
    );
  }
}

export default TrefleTest;
