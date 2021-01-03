
#ifndef _BIT_MATH_
#define _BIT_MATH_

#define SET_BIT(Reg,BitNo)   Reg |= (1<<BitNo)
#define CLR_BIT(Reg,BitNo)   Reg &= (~(1<<BitNo))
#define TOG_BIT(Reg,BitNo)   Reg ^= (1<<BitNo)
#define GET_BIT(Reg,BitNo)   ((Reg>>BitNo)&1)

#define CLEAR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT))



/*check if a specified Bit is Set*/
#define BIT_IS_SET(REG,BIT)      ((REG>>BIT)&1)
/*Check if a specified BIT is Clear*/
#define BIT_IS_CLEAR(REG,BIT)  (!((REG>>BIT)&1))
#endif
