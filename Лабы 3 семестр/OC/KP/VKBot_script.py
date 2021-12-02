import vk_api
from vk_api.longpoll import VkLongPoll, VkEventType
import datetime
import time
import random
from random import randint
from VKBot import ChatBot
from logpas import login, password, token

vk_session = vk_api.VkApi(login, password)
vk_session.auth()
vk_session = vk_api.VkApi(token=token)

session_api = vk_session.get_api()
longpoll = VkLongPoll(vk_session)

print("Starting...")
while True:
	for event in longpoll.listen():
		if event.type == VkEventType.MESSAGE_NEW:
			if event.from_user and not (event.from_me):
				
				print ("Time: " + str(datetime.datetime.now().strftime("%d-%m-%Y %H:%M")))
				print ("Text: " + event.text)
				print ("ID: " + str(event.user_id))

				bot = ChatBot(event.user_id, vk_session)

				vk_session.method('messages.send', bot.new_message(event.text))

				