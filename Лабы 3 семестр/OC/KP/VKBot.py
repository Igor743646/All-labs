import bs4
from bs4 import BeautifulSoup
import requests
import random
from random import randint
import vk_api
from vk_api.longpoll import VkLongPoll, VkEventType
from vk_api.upload import VkUpload
import json
from io import BytesIO
import ctypes

class ChatBot():

	def __init__(self, user_id, vk):
		self.vk = vk
		self._USER_ID = user_id
		self._USER_NAME = self._get_user_name_from_vk_id(user_id)
		self._commands = [['привет', 'хай', 'хэлоу', 'здарово', 'здравствуйте', 'здравствуй'], 
						  ['get file'], ['get files'], ['delete'], ['get size']]

		self.file_library = ctypes.CDLL("/home/igor/Рабочий стол/c/OC/KP/library.so")

	def _get_user_name_from_vk_id(self, user_id):
		request = requests.get("https://vk.com/id"+str(user_id))
		bs = bs4.BeautifulSoup(request.text, "html.parser")
		user_name = self._get_last_first_name(bs.findAll("title")[0])
		return user_name.split()[0]

	def new_message(self, message):
		
		word_list = message.split(' ', maxsplit = 2)

		#Приветствие
		if message.lower() in self._commands[0]:
			a = ("Привет, " + self._USER_NAME + "!")
			return {'user_id': self._USER_ID, 'message': a, 'random_id': randint(-100000, 100000)}
		
		elif message.lower() == 'стоп':
			import dgbvgd

		elif len(word_list) < 2:
			return {'user_id': self._USER_ID, 'message': "Не понимаю о чем ты...", 'random_id': randint(-100000, 100000)}

		#delete path
		elif self._commands[3][0] == word_list[0]:
			df = self.file_library.delete_file
			df.restype = ctypes.c_int
			df.argtypes = [ctypes.c_char_p]
			byte_path = word_list[1].encode('utf8').strip()

			if df(byte_path) == 0:
				return {'user_id': self._USER_ID, 'message': "Файл успешно удалился", 'random_id': randint(-100000, 100000)}
			else:
				return {'user_id': self._USER_ID, 'message': "Файл не смог удалиться", 'random_id': randint(-100000, 100000)}

		#get file path
		elif self._commands[1][0] == word_list[0] + ' ' + word_list[1]:
			gfas = self.file_library.get_file
			gfas.restype = ctypes.c_char_p
			gfas.argtypes = [ctypes.c_char_p]
			byte_path = word_list[2].encode().strip()
			a = gfas(byte_path)
			return {'user_id': self._USER_ID, 'message': a.decode(), 'random_id': randint(-100000, 100000)}

		#get files path
		elif self._commands[2][0] == word_list[0] + ' ' + word_list[1]:
			gfsas = self.file_library.get_files
			gfsas.restype = ctypes.c_char_p
			gfsas.argtypes = [ctypes.c_char_p]
			byte_path = word_list[2].encode().strip()
			a = gfsas(byte_path)
			try:
				res = a.decode(errors = 'ignore')
				return {'user_id': self._USER_ID, 'message': res, 'random_id': randint(-100000, 100000)}
			except:
				return {'user_id': self._USER_ID, 'message': "bad", 'random_id': randint(-100000, 100000)}
			

		#get size path
		elif self._commands[4][0] == word_list[0] + ' ' + word_list[1]:
			gsai = self.file_library.get_file_size
			gsai.restype = ctypes.c_longlong
			gsai.argtypes = [ctypes.c_char_p]
			byte_path = word_list[2].encode('utf8').strip()
			a = gsai(byte_path)
			return {'user_id': self._USER_ID, 'message': str(a), 'random_id': randint(-100000, 100000)}

		else:
			return {'user_id': self._USER_ID, 'message': "Не понимаю о чем ты...", 'random_id': randint(-100000, 100000)}


	@staticmethod
	def _get_last_first_name(tegs_str):
		res = ""
		for i in tegs_str.get_text():
			if i == ' ':
				break
			else:
				res+=i 
		return res
