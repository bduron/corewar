#include <cdk.h>

int main()
{
	CDKSCREEN	*cdkscreen;
	WINDOW		*cursesWin;
	CDKLABEL	*monlabel;
	char		*letexte[3];

	letexte[0] = "Premier programme CDK";
	letexte[1] = "";
	letexte[2] = "Hello World!";
	cursesWin = initscr();
	cdkscreen = initCDKScreen(cursesWin);
	monlabel = newCDKLabel(cdkscreen, CENTER, CENTER, letexte, 3, TRUE, TRUE);
	refreshCDKScreen(cdkscreen);
	waitCDKLabel(monlabel,' ');
	destroyCDKLabel(monlabel);
	destroyCDKScreen(cdkscreen);
	endCDK();
}
