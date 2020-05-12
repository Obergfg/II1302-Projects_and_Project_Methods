import React, { Component } from 'react';

class Button extends Component {
    constructor(props) {
        super(props);
        this.state = {

            status: true
        }

    }


    toggle() {
        this.setState(({ status: !this.state.status }));
    }

    render() {
        const { status } = this.state;
        return (
            <div>
                <button onClick={this.toggle.bind(this)}>toggle</button>
                {status && <div>text</div>}
            </div>
        );
    }
}

export default Button;