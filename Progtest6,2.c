#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */
int odstraneniMezerATab(char * text, int delkaVystupu, int aktDelkaRadku, int poziceSrc, int delkaMezer) 
{    /*odstranuje mezery a tabulator a nahrazuje je mezerou*/
	text[delkaVystupu] = ' ';
	aktDelkaRadku++;
	poziceSrc = poziceSrc + delkaMezer;
}
int odstraneniNewLine(char *text, int delkaVystupu, int aktDelkaRadku, int poziceSrc, int delkaNL)
{ /*odstranuje prebytecne new line v odstavci za 2 new line*/
	text[delkaVystupu] = '\n';
	aktDelkaRadku++;
	text[delkaVystupu] = '\n';
	aktDelkaRadku++;
	poziceSrc = poziceSrc + delkaNL;
}
int zapsaniNewLine(char *text, int delkaVystupu, int aktDelkaRadku)
{	/*zapisuje new line po konci radku*/
	text[delkaVystupu] = '\n';
	delkaVystupu++;
	aktDelkaRadku = 0;
}
int zapsaniSlov(char *text, int delkaVystupu, int delkaSlova, const char *src, int poziceSrc, int aktDelkaRadku)
{	/*zapisuje slova do stringu*/
	int i;
	if (text[delkaVystupu - 1] != '\n' || delkaVystupu != 0)
	{
		text[delkaVystupu] = ' ';
		delkaVystupu++;
	}
	for (i = 0; i <= delkaSlova; i++)
	{
		text[delkaVystupu + i] = src[poziceSrc + i];

	}
	delkaVystupu = delkaVystupu + delkaSlova;
	poziceSrc = poziceSrc + delkaSlova;
	aktDelkaRadku = aktDelkaRadku + delkaSlova;

}

char             * wordWrap                                ( int               width,
                                                             const char      * src )
{
	int delkaVstupu = 0;
	int delkaVystupu = 0;
	int delkaSlova = 0;
	int aktDelkaRadku = 0;
	int poziceSrc = 0;
	int delkaMezer = 0;
	int delkaTab = 0;
	int delkaNL = 0;
	char nechutnejStringMez[53] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
		'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n'};
	char nechutnejStringNL[54] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
		'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '\t' };
	
	delkaVstupu = strlen(src);	
	char *text = (char *)malloc(sizeof(char)* delkaVstupu); // pamet	
	while (src[poziceSrc] != 0) //cteni slov jednotlive
	{
		delkaSlova = strcspn((src+poziceSrc), "\t\n "); /*pocita delku slova*/
		delkaMezer = strcspn(" \t", nechutnejStringMez);/*pocita delku sekvence mezer a tabu*/
		delkaNL = strcspn("\n", nechutnejStringNL);/*pocita delku sekvence new line*/

		if (src[poziceSrc] == ' ' && delkaMezer >= 1){
			odstraneniMezerATab(*text, delkaVystupu, aktDelkaRadku, poziceSrc, delkaMezer);
		}
		if (src[poziceSrc] == '\n' && delkaNL >= 2){
			odstraneniNewLine(*text, delkaVystupu, aktDelkaRadku, poziceSrc, delkaNL);
		}
		if (delkaSlova > width){
			free(text);
			return NULL;
		}

		if (aktDelkaRadku + delkaSlova > width){
			zapsaniNewLine(*text, delkaVystupu, aktDelkaRadku);
		}
		else{
			zapsaniSlov(*text, delkaVystupu, delkaSlova, *src, poziceSrc, aktDelkaRadku );
		}
	}

}

#ifndef __PROGTEST__
int                main                                     ( void )
{
  char * res;
  const char * s0 = 
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
    "libero non diam.";
  const char * s1 = 
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
    "libero non diam.\n"
    "\n"
    "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
    "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
    "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
    "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
    "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
    "Aliquam tempus neque vitae libero molestie ut auctor.\n"
    "\n"
    "\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
    "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
    "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
    "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
    "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
    "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
    "\n";
  res = wordWrap ( 40, s0 );
  assert ( ! strcmp ( res, 
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n" ) );
  free ( res );

  res = wordWrap ( 120, s0 );
  assert ( ! strcmp ( res, 
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
    "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
    "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
    "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
  free ( res );

  res = wordWrap ( 10, s1 );
  assert ( res == NULL );

  res = wordWrap ( 40, s1 );
  assert ( ! strcmp ( res, 
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate\n"
    "id, fringilla sit amet, magna. Nam\n"
    "congue cursus magna. In malesuada, velit\n"
    "a gravida sodales, dolor nisl vestibulum\n"
    "orci, sit amet sagittis mauris tellus\n"
    "nec purus. Nulla eget risus. Quisque nec\n"
    "sapien blandit odio convallis\n"
    "ullamcorper. Lorem ipsum dolor sit amet,\n"
    "consectetuer adipiscing elit.\n"
    "Pellentesque cursus. Aliquam tempus\n"
    "neque vitae libero molestie ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate\n"
    "suscipit. Nam tristique magna nec pede.\n"
    "Sed a nisi. Nulla sed augue ut risus\n"
    "placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien.\n"
    "Nunc facilisis dapibus ipsum. Donec sed\n"
    "mauris. Nulla quam nisi, laoreet non,\n"
    "dignissim posuere, lacinia nec, turpis.\n"
    "Mauris malesuada nisi sed enim. In hac\n"
    "habitasse platea dictumst. Fusce\n"
    "faucibus, turpis nec auctor posuere,\n"
    "nulla tellus scelerisque metus, quis\n"
    "molestie mi dui id quam. Mauris\n"
    "vestibulum. Nam ullamcorper.\n" ) );
  free ( res );

  res = wordWrap ( 80, s1 );
  assert ( ! strcmp ( res, 
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
    "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
    "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
    "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
    "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
    "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
    "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
    "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
    "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
    "ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
    "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
    "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
    "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
    "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
    "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
    "id quam. Mauris vestibulum. Nam ullamcorper.\n" ) );
  free ( res );

  return 0;
}
#endif /* __PROGTEST__ */
