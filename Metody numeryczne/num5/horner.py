def horner(tabl, n, x): 

    result = tabl[0]   

    for i in range(1, n): 
  
        result = result*x + tabl[i] 
   
    return result 