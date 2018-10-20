
/*  Squall Hon   2015.11.11  */

/*  存盘线程头文件  */

#include "p_save.h"

void *Save_thread(void *arg)    //保存线程
{
	wav_hdr_p = &wav_hdr;
	while(1)
	{
		while(savrun != YES);
		savrun = NO;

		if(access(wavpath,0) == 0)	//文件已存在
		{
			int filesize1,filesize2;
			int *filesize1_p = &filesize1;
			int *filesize2_p = &filesize2;

			FILE *fd;
			fd = fopen(wavpath, "a"); 
			if(fd)
			{
				fwrite(buff_second_save,savelen,1,fd);
				fclose(fd);
			}
			fd = fopen(wavpath, "rb+"); 
			if(fd)
			{
				fseek(fd,0x04,SEEK_SET);
				fread(filesize1_p,sizeof(int),1,fd);
				filesize1 = filesize1 + savelen;
				fseek(fd,0x04,SEEK_SET);
				fwrite(filesize1_p,sizeof(int),1,fd);
				fclose(fd);
			}	
			fd = fopen(wavpath, "rb+"); 
			if(fd)
			{
				fseek(fd,0x36,SEEK_SET);
				fread(filesize2_p,sizeof(int),1,fd);
				filesize2 = filesize2 + savelen;
				fseek(fd,0x36,SEEK_SET);
				fwrite(filesize2_p,sizeof(int),1,fd);
				fclose(fd);
			}
			printf("File path is %s\n",wavpath);
			printf("File exists,will be added!\n\n");
		}
		else	//文件不存在
		{
		
			wav_hdr.RIFF[0] = 'R';
			wav_hdr.RIFF[1] = 'I';
			wav_hdr.RIFF[2] = 'F';
			wav_hdr.RIFF[3] = 'F';		
			wav_hdr.size = savelen + 58 - 8;
			wav_hdr.WAVEfmt[0] = 'W';
			wav_hdr.WAVEfmt[1] = 'A';
			wav_hdr.WAVEfmt[2] = 'V';
			wav_hdr.WAVEfmt[3] = 'E';
			wav_hdr.WAVEfmt[4] = 'f';
			wav_hdr.WAVEfmt[5] = 'm';
			wav_hdr.WAVEfmt[6] = 't';
			wav_hdr.WAVEfmt[7] = ' ';
			wav_hdr.ALAW = 0x12;
			wav_hdr.fmttag = 0x06;
			wav_hdr.channel = 0x01;
			wav_hdr.samplespersec = 8192;
			wav_hdr.bytepersec = 8192;
			wav_hdr.blockalign = 0x01;
			wav_hdr.bitpersamples = 0x08;
			wav_hdr.wavefact[0] = 'f';
			wav_hdr.wavefact[1] = 'a';
			wav_hdr.wavefact[2] = 'c';
			wav_hdr.wavefact[3] = 't';
			wav_hdr.temp[0] = 0x04;
			wav_hdr.temp[1] = 0x00;
			wav_hdr.temp[2] = 0x00;
			wav_hdr.temp[3] = 0x00;
			wav_hdr.temp[4] = 0x00;
			wav_hdr.temp[5] = 0x53;
			wav_hdr.temp[6] = 0x07;
			wav_hdr.temp[7] = 0x00;
			wav_hdr.wavedata[0] = 'd';
			wav_hdr.wavedata[1] = 'a';
			wav_hdr.wavedata[2] = 't';
			wav_hdr.wavedata[3] = 'a';
			wav_hdr.allsize = savelen;	
		
			FILE *fd;
			fd = fopen(wavpath, "a"); 
			if(fd)
			{
				printf("File path is %s\n",wavpath);			
				printf("File dose not exists,will be new!\n\n");
				fwrite(wav_hdr_p,58,1,fd);
				fwrite(buff_second_save,savelen,1,fd);
				fclose(fd);
			}
		}
	}
}



