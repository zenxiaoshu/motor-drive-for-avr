#ifndef _SP027_H_
#define _SP027_H_

/*------------------*
*   �� �� �� �� ��  *
*------------------*/
#ifndef TRUE
    # define TRUE    (!0x00)
#endif
#ifndef FALSE
    # define FALSE   0x00
#endif

/********************
*   �� �� �� �� ��  *
********************/
extern void CLS(void);
extern void DisplayINTNum_SP027(long Number);
extern void DisplayFloatNum_SP027(float Num);

#endif       










