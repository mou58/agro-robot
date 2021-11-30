AG=0;
server=fopen('D:\xampp\htdocs\EMA(FINAL)\res.txt','w');
fprintf(server,'0');
fclose(server);
pause(1);
server=fopen('D:\xampp\htdocs\EMA(FINAL)\res.txt','rt');
REA= fscanf(server,'%d')
