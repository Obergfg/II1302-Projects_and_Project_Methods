import React, {Component} from 'react';
import {Line} from 'react-chartjs-2';

/**
 * Chart showing humidity level and sun hours
 */
class Chart extends Component{

  static defaultProps = {
    displayTitle:true,
    displayLegend: true,
    legendPosition:'right',
    
  }
 
  render(){
      
    return (
      <div className="chart">
        <Line
          data={this.props.chartData}
          options={{
            title:{
              display:this.props.displayTitle,
              text:this.props.title,
              fontSize:30
            },
            legend:{
              display:this.props.displayLegend,
              position:this.props.legendPosition
            }
          }}
        />


      </div>
    )
  }
}

export default Chart;