/*****************************************************************/
/* Author  : Ahmed Hamada                                                */
/* SWC     : DIO                                                 */
/* Version : 1.0                                                 */
/* Date    : 07 Dec 2023                                         */
/*****************************************************************/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


#define CONCAT(b7,b6,b5,b4,b3,b2,b1,b0) 	CONCAT_2(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONCAT_2(b7,b6,b5,b4,b3,b2,b1,b0)		0b##b7##b6##b5##b4##b3##b2##b1##b0



#define  PORTA  			*((volatile u8*) 0X3B  )
#define  DDRA  				*((volatile u8*) 0X3A  )
#define  PINA 				*((volatile u8*) 0X39  )


#define  PORTB 				*((volatile u8*) 0X38  )
#define  DDRB 				*((volatile u8*) 0X37  )
#define  PINB  				*((volatile u8*) 0X36  )


#define  PORTC  			*((volatile u8*) 0X35  )
#define  DDRC  				*((volatile u8*) 0X34  )
#define  PINC  				*((volatile u8*) 0X33  )


#define  PORTD  			*((volatile u8*) 0X32  )
#define  DDRD  				*((volatile u8*) 0X31  )
#define  PIND  				*((volatile u8*) 0X30  )

#endif
