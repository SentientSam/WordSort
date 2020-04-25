##############################################
# Author: Samuel Lamb												 #
# Class: cop4530                             #
# Assignment: Assignemnt 6                   # 
# Filename: makefile                         #
# Date Created: 4/23/2020                    #
# Description: makefile for assignment 6     #
##############################################

  
proj6.x :proj6.cpp
	g++ -std=c++11 -o proj6.x proj6.cpp
clean:
	rm *.x