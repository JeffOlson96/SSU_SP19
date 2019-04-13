# Project 2 py, Multiplication of Large Integers
#
#
#
#
#
#


import numpy as np
import math


#computes the size of the number as a string, includes zero's
def size_of_base10(num):
	num_str = str(num)
	count = 0
	for elem in num_str:
		count+=1
	return count

def num_split(num, median):
	# put num into array, split by median, return two lists
	# into high and low
	# iterate until median, while putting numbers into temp arr
	# make sure its the right order or if its reversed then doing some good stuff
	count = 0
	num_str = str(num)
	num_lst = []
	num_list_top = []
	num_list_bottom = []
	# convert number to lists, split lists on median
	for elem in num_str:
		num_lst.append(elem)

	if (len(num_lst) < 2):
		num_list_bottom =  num_lst
		num_list_top.append(0)
		return num_list_top, num_list_bottom


	for elem in num_lst:
		if (count < median):
			num_list_bottom.append(elem)
		elif(count >= median):
			num_list_top.append(elem)
		count+=1

	return num_list_top, num_list_bottom

def convert_to_number(num_list):
	#converts a list to a number
	count = len(num_list)-1
	size_ten_num = 0
	for elem in num_list:
		size_ten_num += int(elem) * (pow(10, count))
		count-=1
	return size_ten_num




def karatsuba(num1, num2):
	if (num1 < 10) or (num2 < 10):
		return num1 * num2

	m_check = max(size_of_base10(num1), size_of_base10(num2))
	m = min(size_of_base10(num1), size_of_base10(num2))
	if (m_check == 1):
		return num1 * num2
	#print("m: ", m)
	m2 = math.floor(m/2)
	low1, high1 = num_split(num1, m2)
	low2, high2  = num_split(num2, m2)


	#convert lists into numbers again
	num_low1 = convert_to_number(low1)
	num_high1 = convert_to_number(high1)
	num_low2 = convert_to_number(low2)
	num_high2 = convert_to_number(high2)
	
	#for elem in low1:
		#print(elem)

	#print("low1: ", num_low1)
	#print("high1: ", num_high1)
	#print("low2: ", num_low2)
	#print("high2: ", num_high2)



	c0 = karatsuba(num_low1, num_low2)
	c2 = karatsuba(num_high1, num_high2)
	c1 = karatsuba((num_low1 + num_high1), (num_low2 + num_high2)) - (c2 + c0) 
	#print(c0)
	#print(c1)
	#print(c2)
	return (c2 * pow(10, (m2 * 2))) + (c1 * pow(10, m2)) + c0


def iseven(x):
	if (x % 2 == 0):
		return True;
	else:
		return False;


def divide_and_conquer(num1, num2):
	#replace all div(a,n) * div(a,n) with karatsuba (div(a,n), div(a,n))
	if (num2 == 0):
		return 1
	elif(iseven(num2)):
		return divide_and_conquer(num1, num2/2) * divide_and_conquer(num1, num2/2)
	else:
		return divide_and_conquer(num1, num2/2) * divide_and_conquer(num1, num2/2) * num1


	
	
	
	
#def decrease_by_constant(num1, num2):
#	if (num2 == 0):
#		return 1
#	elif (num2 == 1):
#		return num1
#	else
#		return decrease_by_constant(num1, num2)
#

def dec_by_one(a,n):
	if (n == 0):
		return 1
	elif (n == 1):
		return a
	else:
		return dec_by_one(a, n-1) * a


def main():
	task = 0
	while(task != 3):
		task = input("Enter 1 for task1, 2 for task2, and 3 to exit..")
		if (task == 1):
			num1 = input("Enter a number: ")
			num2 = input("Enter a second number: ")
			#karatsuba(num1, num2)
			num_karatsuba = karatsuba(num1, num2)
			print(num_karatsuba)
		elif (task == 2):
			num1 = input("Enter a number: ")
			num2 = input("Enter a second number: ")
			#expo = dec_by_one(num1, num2)
			expo1 = divide_and_conquer(num1, num2)
			#print("number dec_by_one: ", expo)
			print("number divide_and_conquer: ", expo1)



main()




