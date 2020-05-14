export const WEATHERAPI = 'https://api.openweathermap.org/data/2.5/forecast?q=';
export const WEATHERAPIKEY = '&appid=c8e65a4f40a9f86173cf5e60e03219c8';



export const dayfunc123 = (city) => {
    var url = WEATHERAPI + city + WEATHERAPIKEY;
    fetch(url)
    .then(response =>
    {
        if ( response.status >= 200 && response.status <299) {
            return response.json();
        } else {
            throw Error(response.statusText);
        }
        
    }).then(data => {
    }).catch((error) => {
        console.log(error);
    });

}