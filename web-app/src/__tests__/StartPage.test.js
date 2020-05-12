/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200508
 *Date of  update: -
 *Code Properties: The code tests the functionality of StartPage.js.
*/


import React from 'react';
import Adapter from 'enzyme-adapter-react-16';
import StartPage from '../StartPage/StartPage';
import user from '../UserAccount/UserAccount'
import Enzyme, { shallow } from 'enzyme';

Enzyme.configure({ adapter: new Adapter() });


describe('testing startPage.js', () => {
  

  /*
  *Test cases for the 'signUp' ActiveForm state
  */
  it('should contain the text "Create an account"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const div = wrapper.find('div').at(1);
    expect(div.text()).toBe('Create an account');
  });

  it('should contain the text "Sign up"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const div = wrapper.find('div div').at(2);
    expect(div.text()).toBe('Sign up');

  });

  it('should contain the button text "Sign up"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(0);
    expect(button.text()).toBe('Sign up');

  });

  it('should contain the button text "Log in"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    expect(button.text()).toBe('log in');

  });

  it('should contain the button text "Reset password"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(2);
    expect(button.text()).toBe('Reset password');

  });

  it('should contain the button text "email"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const input = wrapper.find('input').at(0);
    expect(input.prop('placeholder')).toBe('email');
  });

  it('should contain the button text "password"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const input = wrapper.find('input').at(1);
    expect(input.prop('placeholder')).toBe('password');

  });

  it('should receive email input', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const input = wrapper.find('input').at(0);
    input.prop('onChange')({ target: { value: 'email input' } });
    expect(wrapper.state('email')).toBe('email input');

  });

  it('should receive password input', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const input = wrapper.find('input').at(1);
    input.prop('onChange')({ target: { value: 'password input' } });
    expect(wrapper.state('password')).toBe('password input');

  });



  /*
  *Test cases for the 'logIn' ActiveForm state
  */
  it('should contain the text "Welcome back!"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const div = wrapper.find('div').at(1);
    expect(div.text()).toBe('Welcome back!');

  });

  it('should contain the text "Log in"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const div = wrapper.find('div div').at(2);
    expect(div.text()).toBe('Log in');

  });

  it('should contain the button text "Log in"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const button2 = wrapper.find('button').at(0);
    expect(button2.text()).toBe('Log in');

  });

  it('should contain the button text "sign up"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const button2 = wrapper.find('button').at(1);
    expect(button2.text()).toBe('sign up');

  });

  it('should contain the button text "Reset password"', () => {
    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const button2 = wrapper.find('button').at(2);
    expect(button2.text()).toBe('Reset password');

  });

  it('should contain the form text "email"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const input = wrapper.find('input').at(0);
    expect(input.prop('placeholder')).toBe('email');  
  });

  it('should contain the button text "password"', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const input = wrapper.find('input').at(1);
    expect(input.prop('placeholder')).toBe('password');

  });

  it('should receive email input', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const input = wrapper.find('input').at(0);
    input.prop('onChange')({target:{value: 'email input'}});
    expect(wrapper.state('email')).toBe('email input');

  });

  it('should receive password input', () => {

    const wrapper = shallow(<StartPage currentUser={user} />);
    const button = wrapper.find('button').at(1);
    button.simulate('click');
    const input = wrapper.find('input').at(1);
    input.prop('onChange')({target:{value: 'password input'}});
    expect(wrapper.state('password')).toBe('password input');

  });

});
