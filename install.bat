@echo off

if not exist src\Debug mkdir src\Debug
copy lib\SDL\*.dll src\Debug
copy lib\noise\*.dll src\Debug