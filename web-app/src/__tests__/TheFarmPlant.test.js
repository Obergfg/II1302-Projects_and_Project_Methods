
import Adapter from 'enzyme-adapter-react-16';

import Enzyme, { shallow } from 'enzyme';

Enzyme.configure({adapter: new Adapter()});


describe('testing TheFarmPlant.js', () => {

  it('should be true', () => {
    expect(true)
    .toBe(true);
  });

});
