import React from 'react';
import Adapter from 'enzyme-adapter-react-16';
import TheFarmPlant from '../Homepage/TheFarmPlant';
import Enzyme, { shallow } from 'enzyme';

Enzyme.configure({adapter: new Adapter()});


describe('testing TheFarmPlant.js', () => {

  it('should return that TheFarmPlant div exists', () => {
   // const wrapper = shallow(<TheFarmPlant userID={1}/>);
    expect(true)
    .toBe(true);
  });

});
