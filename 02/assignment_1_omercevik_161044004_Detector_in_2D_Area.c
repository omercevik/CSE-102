/*
											CSE 102 Homework Assignment 1 

												OMER_CEVIK_161044004

					# 	We are trying to find out the marked region with using a detector in 2D areas.	 #
					# 	And we check out if we find it or made a partial hit or missed the target.  	 # 

																											*/

#include <stdio.h> 				/* We use do while , if , else , printf and scanf etc. functions  */

int main(int argc, char const *argv[])
{
	/* 		
			Declaring counter, Hits' X and Y sizes, Board's, MarkedRegion's and Detector's size and their sides and their corners.
			Declaring SumOfHits X and Y sizes.
	*/
	int CounterOfAttempts, BOARD_X, BOARD_Y, BoardLeftUp_X, BoardLeftUp_Y, BoardLeftDown_X, BoardLeftDown_Y, BoardRightUp_X, BoardRightUp_Y,
			BoardRightDown_X, BoardRightDown_Y, MARKED_X, MARKED_Y;

	float CenterOfMarked_X, CenterOfMarked_Y, LeftCenterOfMarked_X, LeftCenterOfMarked_Y, LeftUpOfMarked_X, LeftUpOfMarked_Y,
			LeftDownOfMarked_X, LeftDownOfMarked_Y, RightCenterOfMarked_X, RightCenterOfMarked_Y, RightUpOfMarked_X, RightUpOfMarked_Y,
			RightDownOfMarked_X, RightDownOfMarked_Y, UpCenterOfMarked_X, UpCenterOfMarked_Y, DownCenterOfMarked_X, DownCenterOfMarked_Y;

	float DETECTOR_X, DETECTOR_Y, LeftCenterOfDetector_X, LeftCenterOfDetector_Y, LeftUpOfDetector_X, LeftUpOfDetector_Y,
			LeftDownOfDetector_X, LeftDownOfDetector_Y, RightCenterOfDetector_X, RightCenterOfDetector_Y, RightUpOfDetector_X, RightUpOfDetector_Y,
			RightDownOfDetector_X, RightDownOfDetector_Y, UpCenterOfDetector_X, UpCenterOfDetector_Y, DownCenterOfDetector_X, DownCenterOfDetector_Y,
			SumOfHit_X, SumOfHit_Y, x = 0.0, y = 0.0;
	
	BOARD_X = 200; /* Initialize Board's X size.  */
	BOARD_Y = 300; /* Initialize Board's Y size.  */

	BoardLeftDown_X = 0;		/* Initialize Board's Left Down corner's X size.    */
	BoardLeftDown_Y = BOARD_Y;	/* Initialize Board's Left Down corner's Y size.    */
	BoardLeftUp_X = 0;			/* Initialize Board's Left Up corner's X size.      */
	BoardLeftUp_Y = 0;			/* Initialize Board's Left Up corner's Y size.      */
	BoardRightUp_X = BOARD_X;	/* Initialize Board's Right Up corner's X size.     */
	BoardRightUp_Y = 0;			/* Initialize Board's Right Up corner's Y size.     */
	BoardRightDown_X = BOARD_X; /* Initialize Board's Right Down corner's X size.   */
	BoardRightDown_Y = BOARD_Y; /* Initialize Board's Right Down corner's Y size.   */
	

	MARKED_X = 15;		/*  Initialize MarkedRegion's X size.      */
	MARKED_Y = 20;		/*  Initialize MarkedRegion's X size.      */

	CenterOfMarked_X = 50.0;		/*  Initialize MarkedRegion' Center's X size. */
	CenterOfMarked_Y = 40.0;		/*  Initialize MarkedRegion' Center's Y size. */
	LeftCenterOfMarked_X = CenterOfMarked_X - MARKED_X/2;		/*  Declare MarkedRegion' Left Side Center's X size.    */
	LeftCenterOfMarked_Y = CenterOfMarked_Y;					/*  Declare MarkedRegion' Left Side Center's Y size.    */
	LeftUpOfMarked_X = CenterOfMarked_X - MARKED_X/2;			/*  Declare MarkedRegion' Left Up corner's X size. 		*/
	LeftUpOfMarked_Y = CenterOfMarked_Y - MARKED_Y/2;			/*  Declare MarkedRegion' Left Up corner's Y size.		*/
	LeftDownOfMarked_X = CenterOfMarked_X - MARKED_X/2;			/*  Declare MarkedRegion' Left Down corner's X size. 	*/
	LeftDownOfMarked_Y = CenterOfMarked_Y + MARKED_Y/2;			/*  Declare MarkedRegion' Left Down corner's Y size. 	*/
	RightCenterOfMarked_X = CenterOfMarked_X + MARKED_X/2;		/*  Declare MarkedRegion' Right Side Center's X size. 	*/
	RightCenterOfMarked_Y = CenterOfMarked_Y;					/*  Declare MarkedRegion' Right Side Center's Y size. 	*/
	RightUpOfMarked_X = CenterOfMarked_X + MARKED_X/2;			/*  Declare MarkedRegion' Right Up corner's X size. 	*/
	RightUpOfMarked_Y = CenterOfMarked_Y - MARKED_Y/2;			/*  Declare MarkedRegion' Right Up corner's Y size. 	*/
	RightDownOfMarked_X = CenterOfMarked_X + MARKED_X/2;		/*  Declare MarkedRegion' Right Down corner's X size. 	*/
	RightDownOfMarked_Y = CenterOfMarked_Y + MARKED_Y/2;		/*  Declare MarkedRegion' Right Down corner's Y size. 	*/
	UpCenterOfMarked_X = CenterOfMarked_X;						/*  Declare MarkedRegion' Up Side Center's X size.    	*/
	UpCenterOfMarked_Y = CenterOfMarked_Y - MARKED_Y/2;			/*  Declare MarkedRegion' Up Side Center's Y size.    	*/
	DownCenterOfMarked_X = CenterOfMarked_X;					/*  Declare MarkedRegion' Down Side Center's X size.    */
	DownCenterOfMarked_Y = CenterOfMarked_Y + MARKED_Y/2;		/*  Declare MarkedRegion' Down Side Center's Y size.    */

	
	DETECTOR_X = 20.00;	/*  Initialize Detector's X size.  */
	DETECTOR_Y = 20.00;	/*  Initialize Detector's Y size.  */

	CounterOfAttempts = 10;		/*  Initialize the Counter of Attempts. */
	
	/* 		We prints 2D size of Board, MarkedRegion and Detector.		*/

	printf("Board = [%d x %d], marked region = [%d x %d], Detector = [%.2f x %.2f]\n",BOARD_X,BOARD_Y,MARKED_X,MARKED_Y,DETECTOR_X,DETECTOR_Y);

	do 		/*  We use do while function for to calculate attempts counter.   */
	{
		printf("Enter the x coordinate of the move:\n");	/*  We print and scan x the position of detector's center from user.  */
		scanf("%f",&x);
		printf("Enter the y coordinate of the move:\n");	/*  We print and scan y the position of detector's center from user.  */
		scanf("%f",&y);

		LeftCenterOfDetector_X = x - DETECTOR_X/2;				/*  Declare Detector' Left Side Center's X size.    */
		LeftCenterOfDetector_Y = y;								/*  Declare Detector' Left Side Center's Y size.    */
		LeftUpOfDetector_X = x - DETECTOR_X/2;					/*  Declare Detector' Left Up corner's X size. 		*/
		LeftUpOfDetector_Y = y - DETECTOR_Y/2;					/*  Declare Detector' Left Up corner's Y size. 		*/
		LeftDownOfDetector_X = x - DETECTOR_X/2;				/*  Declare Detector' Left Down corner's X size. 	*/
		LeftDownOfDetector_Y = y + DETECTOR_Y/2;				/*  Declare Detector' Left Down corner's Y size. 	*/
		RightCenterOfDetector_X = x + DETECTOR_X/2;				/*  Declare Detector' Right Side Center's X size. 	*/
		RightCenterOfDetector_Y = y;							/*  Declare Detector' Right Side Center's Y size. 	*/
		RightUpOfDetector_X = x + DETECTOR_X/2;					/*  Declare Detector' Right Up corner's X size. 	*/
		RightUpOfDetector_Y = y - DETECTOR_Y/2;					/*  Declare Detector' Right Up corner's Y size. 	*/
		RightDownOfDetector_X = x + DETECTOR_X/2;				/*  Declare Detector' Right Down corner's X size. 	*/
		RightDownOfDetector_Y = y + DETECTOR_Y/2;				/*  Declare Detector' Right Down corner's Y size. 	*/
		UpCenterOfDetector_X = x;								/*  Declare Detector' Up Side Center's X size.    	*/
		UpCenterOfDetector_Y = y - DETECTOR_Y/2;				/*  Declare Detector' Up Side Center's Y size.    	*/
		DownCenterOfDetector_X = x;								/*  Declare Detector' Down Side Center's X size.    */
		DownCenterOfDetector_Y = y + DETECTOR_Y/2;				/*  Declare Detector' Down Side Center's Y size.    */

		if ( ((x == CenterOfMarked_X) && (y == CenterOfMarked_Y)) || (((LeftDownOfDetector_X <= LeftDownOfMarked_X) && 
					(LeftDownOfDetector_Y >= LeftDownOfMarked_Y)) && ((RightUpOfDetector_X >= RightUpOfMarked_X) && (RightUpOfDetector_Y <= RightUpOfMarked_Y))
					&& ((LeftUpOfDetector_X <= LeftUpOfMarked_X) && (LeftUpOfDetector_Y <= LeftUpOfMarked_Y)) && ((RightDownOfDetector_X >= RightDownOfMarked_X) && (RightDownOfDetector_Y >= RightDownOfMarked_Y))) ) /* Cheking for if user win.  */
		{
			printf("Congratulations.. You win the game!!!\n");	/* If user win we congrats him/her and print it to screen.  */
			break;	/* Game is over so we have to end the loop.  */
		}
		if ( (x < BoardLeftDown_X) || (x > BoardRightDown_X) || ((x < BoardLeftUp_X) || (x > BoardRightUp_X ) || (y > BoardLeftDown_Y) || (y > BoardRightDown_Y)
				|| (y < BoardLeftUp_Y) || (y < BoardRightUp_Y)) || ((RightUpOfDetector_X > BoardRightUp_X) || (LeftUpOfDetector_X < BoardLeftUp_X)) || 
				((LeftDownOfDetector_X < BoardLeftDown_X) || (RightUpOfDetector_X > BoardRightUp_X)) || ((RightUpOfDetector_Y < BoardRightUp_Y) || (LeftUpOfDetector_Y < BoardLeftUp_Y))
				|| ((RightDownOfDetector_Y > BoardRightDown_Y) || (LeftDownOfDetector_Y > BoardRightDown_Y)))	/* Checking if user's inputs are on the board or not */
		{
			--CounterOfAttempts;		/*  If user enter an unacceptable coordination then we decrease 1 the counter of attempts and printing error message. */
			printf("Error, move is not valid. Try again. Attempts remaining: %d\n",CounterOfAttempts );
		}
		else if ( (LeftCenterOfDetector_X > RightCenterOfMarked_X) || (RightCenterOfDetector_X < LeftCenterOfMarked_X) 
				|| (UpCenterOfDetector_Y > DownCenterOfMarked_Y) || (DownCenterOfDetector_Y < UpCenterOfMarked_Y) )		/* Checking if user missed the target or not.  */
		{
			--CounterOfAttempts;	/*  If user missed the target then we decrease 1 the counter of attempts and printing missed message.  */
			printf("You missed the target, attempts remaining: %d\n",CounterOfAttempts );
		}
		else if ( ((LeftUpOfDetector_X < RightCenterOfMarked_X) && (LeftUpOfDetector_X >= LeftCenterOfMarked_X)) && ((LeftUpOfDetector_Y >= UpCenterOfMarked_Y)
				&& (LeftUpOfDetector_Y < DownCenterOfMarked_Y)) )	/* Checking if user made a partial hit of detector's left up corner. */
		{
			SumOfHit_X = RightCenterOfMarked_X - LeftUpOfDetector_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = DownCenterOfMarked_Y - LeftUpOfDetector_Y;		/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftDownOfDetector_X < RightCenterOfMarked_X) && (LeftDownOfDetector_X >= LeftCenterOfMarked_X)) && ((LeftDownOfDetector_Y >= UpCenterOfMarked_Y)
				&& (LeftDownOfDetector_Y <= DownCenterOfMarked_Y)))	/* Checking if user made a partial hit of detector's left down corner. */
		{ 
			SumOfHit_X = RightCenterOfMarked_X - LeftDownOfDetector_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = LeftDownOfDetector_Y - UpCenterOfMarked_Y;		/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((RightDownOfDetector_X <= RightCenterOfMarked_X) && (RightDownOfDetector_X > LeftCenterOfMarked_X)) && ((RightDownOfDetector_Y > UpCenterOfMarked_Y)
				&& (RightDownOfDetector_Y <= DownCenterOfMarked_Y)))	/* Checking if user made a partial hit of detector's right down corner. */
		{ 
			SumOfHit_X = RightDownOfDetector_X - LeftCenterOfMarked_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = RightDownOfDetector_Y - UpCenterOfMarked_Y;	/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((RightUpOfDetector_X <= RightCenterOfMarked_X) && (RightUpOfDetector_X > LeftCenterOfMarked_X)) && ((RightUpOfDetector_Y >= UpCenterOfMarked_Y)
				&& (RightUpOfDetector_Y < DownCenterOfMarked_Y)) )	/* Checking if user made a partial hit of detector's right up corner. */
		{
			SumOfHit_X = RightUpOfDetector_X - LeftCenterOfMarked_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = DownCenterOfMarked_Y - RightUpOfDetector_Y;	/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((RightUpOfMarked_X <= RightCenterOfDetector_X) && (RightUpOfMarked_X > LeftCenterOfDetector_X)) && ((RightUpOfMarked_Y >= UpCenterOfDetector_Y)
				&& (RightUpOfMarked_Y < DownCenterOfDetector_Y)) && ((RightDownOfMarked_X <= RightCenterOfDetector_X) && (RightDownOfMarked_X > LeftCenterOfDetector_X)) && ((RightDownOfMarked_Y > UpCenterOfDetector_Y)
				&& (RightDownOfMarked_Y <= DownCenterOfDetector_Y)) )	/* Checking if user made a partial hit of MarkedRegion's left side. */
		{
			SumOfHit_X = RightUpOfMarked_X - LeftCenterOfDetector_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = RightDownOfMarked_Y - RightUpOfMarked_Y;		/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftUpOfMarked_X < RightCenterOfDetector_X) && (LeftUpOfMarked_X >= LeftCenterOfDetector_X)) && ((LeftUpOfMarked_Y >= UpCenterOfDetector_Y)
				&& (LeftUpOfMarked_Y < DownCenterOfDetector_Y)) && ((LeftDownOfMarked_X < RightCenterOfDetector_X) && (LeftDownOfMarked_X >= LeftCenterOfDetector_X)) && ((LeftDownOfMarked_Y > UpCenterOfDetector_Y)
				&& (LeftDownOfMarked_Y <= DownCenterOfDetector_Y)) )	/* Checking if user made a partial hit of MarkedRegion's right side. */
		{
			SumOfHit_X = RightCenterOfDetector_X - LeftUpOfMarked_X;	/* Calculating the hits' X size. */
			SumOfHit_Y = LeftDownOfMarked_Y - LeftUpOfMarked_Y;			/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftDownOfMarked_X < RightCenterOfDetector_X) && (LeftDownOfMarked_X >= LeftCenterOfDetector_X)) && ((LeftDownOfMarked_Y > UpCenterOfDetector_Y)
				&& (LeftDownOfMarked_Y <= DownCenterOfDetector_Y)) && ((RightDownOfMarked_X <= RightCenterOfDetector_X) && (RightDownOfMarked_X > LeftCenterOfDetector_X)) && ((RightDownOfMarked_Y > UpCenterOfDetector_Y)
				&& (RightDownOfMarked_Y <= DownCenterOfDetector_Y)) )	/* Checking if user made a partial hit of MarkedRegin's down side. */
		{
			SumOfHit_X = RightDownOfMarked_X - LeftDownOfMarked_X;		/* Calculating the hits' X size. */
			SumOfHit_Y = LeftDownOfMarked_Y - UpCenterOfDetector_Y;		/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftUpOfMarked_X < RightCenterOfDetector_X) && (LeftUpOfMarked_X >= LeftCenterOfDetector_X)) && ((LeftUpOfMarked_Y <= DownCenterOfDetector_Y)
				&& (LeftUpOfMarked_Y > DownCenterOfDetector_Y)) && ((RightUpOfMarked_X <= RightCenterOfDetector_X) && (RightUpOfMarked_X > LeftCenterOfDetector_X)) && ((RightUpOfMarked_Y >= UpCenterOfDetector_Y)
				&& (RightUpOfMarked_Y < DownCenterOfDetector_Y)) )	/* Checking if user made a partial hit of MarkedRegion's up side. */
		{
			SumOfHit_X = RightUpOfMarked_X - LeftUpOfMarked_X;				/* Calculating the hits' X size. */
			SumOfHit_Y = DownCenterOfDetector_Y - UpCenterOfMarked_Y;		/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((RightUpOfMarked_X >= RightUpOfDetector_X) && (RightUpOfMarked_Y <= RightUpOfDetector_Y)) && ((RightDownOfMarked_X >= RightDownOfDetector_X) && (RightDownOfMarked_Y >= RightDownOfDetector_Y))
				&& ((LeftUpOfMarked_X <= LeftUpOfDetector_X) && (LeftUpOfMarked_Y <= LeftUpOfDetector_Y)) && ((LeftDownOfMarked_X <= LeftDownOfDetector_X) 
					&& (LeftDownOfMarked_Y >= LeftDownOfDetector_Y)) )	/* Checking if user made partial hit with detector inside of marked region. */
		{
			SumOfHit_X = RightUpOfDetector_X - LeftUpOfDetector_X;				/* Calculating the hits' X size. */
			SumOfHit_Y = RightDownOfDetector_Y - RightUpOfMarked_Y;				/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftDownOfMarked_X >= LeftDownOfDetector_X) && (RightDownOfMarked_X <= RightDownOfDetector_X)) && ((UpCenterOfDetector_Y < DownCenterOfMarked_Y)))
		{			/* Checking if user made a partial hit with detector > MarkedRegion and hits up of MarkedRegion. */
			SumOfHit_X = RightUpOfMarked_X - LeftUpOfMarked_X;				/* Calculating the hits' X size. */
			SumOfHit_Y = RightDownOfMarked_Y - RightUpOfDetector_Y;				/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}
		else if ( ((LeftUpOfMarked_X >= LeftDownOfDetector_X) && (RightUpOfMarked_X <= RightDownOfDetector_X)) && ((DownCenterOfDetector_Y > UpCenterOfMarked_Y)))
		{			/* Checking if user made a partial hit with detector > MarkedRegion and hits down of MarkedRegion. */
			SumOfHit_X = RightDownOfMarked_X - LeftDownOfMarked_X;				/* Calculating the hits' X size. */
			SumOfHit_Y = RightDownOfMarked_Y - RightUpOfDetector_Y;				/* Calculating the hits' Y size. */

			MARKED_X = SumOfHit_X;	/* Creating a new MarkedRegion X side. */
			MARKED_Y = SumOfHit_Y;	/* Creating a new MarkedRegion Y side. */

			CenterOfMarked_X = MARKED_X/2;	/* New x coordinate of MarkedRegion. */
			CenterOfMarked_Y = MARKED_Y/2;	/* New y coordinate of Markedregion. */

			DETECTOR_X /= 2;	/* It is the rule if user just made a partial hit, then we make detector's X way smaller.   */
			DETECTOR_Y /= 2;	/* It is the rule if user just made a partial hit, then we make detector's Y way smaller.   */
			--CounterOfAttempts;	/* Decreasing counter of attempts 1. Because user just made a partial hit. */

			/*  We print how much hit made the user and how much marked region and detector were shirked to. */

			printf("Partial hit! marked region was shirked to [%.1f x %.1f], detector was shirked to [%.2f x %.2f] \nattempts remaining: %d\n",SumOfHit_X, SumOfHit_Y, DETECTOR_X, DETECTOR_Y, CounterOfAttempts);
		}

	}while( CounterOfAttempts > 0 );	/*  It checks the counter in the loop */

	return 0;	/*  Ending programme truely.  */
}