const WEATHERAPI = 'https://api.openweathermap.org/data/2.5/forecast?q=';
const WEATHERAPIKEY = '&appid=c8e65a4f40a9f86173cf5e60e03219c8';


function dayfunc(city) {
    var url = WEATHERAPI + city + WEATHERAPIKEY;
    fetch(url)
    .then(response =>
    {
        return response.json();
    }).then(data => {
        console.log(data)
        this.drawWeather1(data);
    });
}