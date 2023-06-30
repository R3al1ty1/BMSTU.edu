import requests
import datetime


def getweather(city):
    try:
        token = '09a6752dd2fe68a2eda560735e8898d3'
        url = f'http://api.openweathermap.org/geo/1.0/direct?q={city}&limit=1&appid={token}'
        r = requests.get(url)
        colData = r.json()
        lon = colData[0]['lon']
        lat = colData[0]['lat']

        url = f'https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={token}&units=metric'
        r = requests.get(url)
        colData = r.json()

        city = colData["name"]
        temp = colData["main"]["temp"]
        feelsLike = colData["main"]["feels_like"]
        pressure = colData["main"]["pressure"]
        humidity = colData["main"]["humidity"]
        tempMin = colData["main"]["temp_min"]
        tempMax = colData["main"]["temp_max"]
        windSpeed = colData["wind"]["speed"]
        sunrise = datetime.datetime.fromtimestamp(colData["sys"]["sunrise"])
        sunset = datetime.datetime.fromtimestamp(colData["sys"]["sunset"])
        dayLength = sunset - sunrise

        print(f'Погода в городе {city} на {datetime.datetime.now().strftime("%d.%m.%Y %H:%M")}:\n'
              f'Температура: {temp}°C, ощущается как {feelsLike}°C\n\n'
              f'Температура от {tempMin}°C до {tempMax}°C\n'
              f'Давление: {pressure} мм рт. ст., влажность: {humidity}\n'
              f'Скорость ветра: {windSpeed} м/с\n'
              f'Восход: {sunrise}\n'
              f'Закат: {sunset}\n'
              f'Продолжительность дня: {dayLength}\n')
    except Exception:
        return 'Проверьте введенный Вами город'

if __name__ == '__main__':
    print(getweather('Moscow'))