import React from 'react';
import Adapter from 'enzyme-adapter-react-16';
import Button from './button';
import Enzyme, { shallow } from 'enzyme';

Enzyme.configure({ adapter: new Adapter() });

describe('testing button.js', () => {

    it('should show toggle', () => {
      const wrapper = shallow(<Button />);
      const text = wrapper.find('button');
      expect(text.text()).toBe('toggle');
    });
  
    it('finds text in div', () => {
      const wrapper = shallow(<Button />);
      const div = wrapper.find('div div');
      expect(div.text()).toBe('text');
    });
    
    it('should hide text when button is pressed', () => {
        const wrapper = shallow(<Button />);
        const button = wrapper.find('button');
        button.simulate('click');
        const text = wrapper.find('div div');
        expect(text.length).toBe(1);
    });
  
  
  });
  