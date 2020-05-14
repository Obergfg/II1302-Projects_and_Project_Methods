import React from 'react';
import Adapter from 'enzyme-adapter-react-16';
import HomePage from '../HomePage/HomePage';
import Enzyme, { shallow } from 'enzyme';
import user from '../UserAccount/UserAccount.js'

Enzyme.configure({adapter: new Adapter()});


const mockUser = { getUser: () => true,
                   addObserver: () => true
                 }

describe('testing HomePage.js', () => {

  it('should contain no text', () => {
    const wrapper = shallow(<HomePage currentUser={user}/>);
    const div = wrapper.find('div');
    expect(div.text()).toBe('');
  });

  it('should return that HomePageContainer exists', () => {
    const wrapper = shallow(<HomePage currentUser={mockUser}/>);
    expect(wrapper.find('div div')
    .hasClass('HomePageContainer'))
    .toBe(true);
  });

  it('should return a <TheFarmPlant /> component', () => {
    const wrapper = shallow(<HomePage currentUser={mockUser}/>);
    const div = wrapper.find('div').at(0);
    expect(div.text()).toBe('<TheFarmPlant />');
  });

  it('should return a <TheFarmPlant /> component', () => {
    const wrapper = shallow(<HomePage currentUser={mockUser}/>);
    const div = wrapper.find('div').at(1);
    expect(div.text()).toBe('<TheFarmPlant />');
  });


});
