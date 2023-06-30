import datetime
import requests
from aiogram import Bot, Dispatcher, executor, types
from aiogram.contrib.fsm_storage.memory import MemoryStorage
from aiogram.dispatcher import FSMContext
from aiogram.dispatcher.filters.state import State, StatesGroup

tgToken = '5874568638:AAEZl_PPbWS1w1LpRWZEhKlSeSXwpxfhJS0'
bot = Bot(token=tgToken)
dp = Dispatcher(bot, storage= MemoryStorage())

@dp.message_handler(commands=['start'])
async def processStartCommand(message: types.Message):
    kb = [
        [types.KeyboardButton(text="Возможности")],
        [types.KeyboardButton(text="Полная информация")],
        [types.KeyboardButton(text="Краткая сводка")],
    ]
    keyboard = types.ReplyKeyboardMarkup(
        keyboard=kb,
        resize_keyboard=True,
        input_field_placeholder="Введите желаемое действие"
    )

    await message.answer(
        'Привет, я бот, который умеет показывать погоду в любом городе. Напиши мне название города, а я покажу тебе погоду в нем.',
        reply_markup=keyboard)

@dp.message_handler(lambda message: message.text =='Возможности')
async def capabilities(message: types.Message):
    await message.answer('Бот показывает погоду в выбранном Вами городе, а также различные данные, такие как восход и закат, продолжительность дня и многое другое!')

class Form(StatesGroup):
    city = State()
    partCity = State()

@dp.message_handler(state=Form.city)
async def processCity(message: types.Message, state: FSMContext):
    await state.finish() # <-- Here we get the name
    city = message.text
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

        await message.reply(f'Погода в городе {city} на {datetime.datetime.now().strftime("%d.%m.%Y %H:%M")}:\n'
              f'Температура: {temp}°C, ощущается как {feelsLike}°C\n\n'
              f'Температура от {tempMin}°C до {tempMax}°C\n'
              f'Давление: {pressure} мм рт. ст., влажность: {humidity}\n'
              f'Скорость ветра: {windSpeed} м/с\n'
              f'Восход: {sunrise}\n'
              f'Закат: {sunset}\n'
              f'Продолжительность дня: {dayLength}\n')
    except Exception:
        await message.reply('Проверьте введенный Вами город')

@dp.message_handler(state=Form.partCity)
async def partProcessCity(message: types.Message, state: FSMContext):
    await state.finish() # <-- Here we get the name
    city = message.text
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

        await message.reply(f'Погода в городе {city} на {datetime.datetime.now().strftime("%d.%m.%Y %H:%M")}:\n'
              f'Температура: {temp}°C, ощущается как {feelsLike}°C\n\n'
              f'Температура от {tempMin}°C до {tempMax}°C\n'
              f'Давление: {pressure} мм рт. ст., влажность: {humidity}')
    except Exception:
        await message.reply('Проверьте введенный Вами город')

@dp.message_handler(lambda message: message.text =='Полная информация')
async def fullInfo(message: types.Message):
    await message.reply('Введите название города, чтобы узнать погоду в нем.')
    await Form.city.set()

@dp.message_handler(lambda message: message.text =='Краткая сводка')
async def partInfo(message: types.Message):
    await message.answer('Введите название города, чтобы узнать погоду в нем.')
    await Form.partCity.set()

if __name__ == '__main__':
    executor.start_polling(dp)