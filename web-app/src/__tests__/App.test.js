import React from 'react';
import Adapter from 'enzyme-adapter-react-16';
import App from '../App';
import Enzyme, { shallow } from 'enzyme';

Enzyme.configure({adapter: new Adapter()});


describe('testing app.js', () => {

  it('should show true', () => {
    const wrapper = true;
    expect(true).toBe(true);
  });



});
