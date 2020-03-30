import React, { Component } from "react";

/*
  Author: Max
  Co-Authors:
  Date of creation: 20-03-24
  Date of update: 20-03-24
  Code Properties: Component made to test the Trefle API.
*/

var TOKEN = "bVdrbVFaTkV4YTNnUnFWNk5EaVR1QT09"

class TrefleTest extends Component {
  constructor(props){
    super(props);

    this.state = {
      searchPhrase: "",
      results: <p>Placeholder for Trefle API test...</p>,
      plants: [],
    };

    this.handleChange = this.handleChange.bind(this);
    this.searchPlant = this.searchPlant.bind(this);
    this.updateSearchList = this.updateSearchList.bind(this);

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

    //plants?scientific_name={NAME} searches for scientific names only
    //plants?common_name={NAME} searches for the commong name only
    //plants?q={NAME} searches both scientific and common name
    //There are other search alternatives as well, check trefle.io/reference
    fetch("https://trefle.io/api/plants?q="+this.state.searchPhrase+"&token="+TOKEN)
    .then(r => r.json())
    .then(this.updateSearchList)

    this.setState({
      "results": <div className="results"><p>Plant for {this.state.searchPhrase} result...</p></div>
    })
  }

  updateSearchList(json){
    if(json === undefined || json == 0) {
      console.log("No plant found...");
    }
    this.setState({
      "plants": json
    });
  }

  render() {
    return (
      <div className="TreffleTest">
        <input value={this.state.searchPhrase} onChange={this.handleChange} name="searchPhrase" placehold="Search"></input>
        <button type="submit" onClick={this.searchPlant}>Search</button>
        {this.state.results}
        <div className="plants">
          {this.state.plants.map((p, i) => (
            <div key={i}>
              <p>
              id: {p.id}<br/>
              slug: {p.slug}<br/>
              scientific name: {p.scientific_name}<br/>
              common name: {p.common_name}
              </p>
            </div>
          ))}
        </div>
      </div>
    );
  }
}

export default TrefleTest;
