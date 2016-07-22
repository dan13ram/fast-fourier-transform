sizes<-sample(8192:8192,10,replace = TRUE);
sink("test");
for(i in 1:10)
{
    u<-runif(sizes[i],0,1);
    cat(u,sep=" ",append=TRUE);
    if(i%%2 == 0)
        {
            cat("\n\n",append=TRUE);
        }
    else
        {
            cat("\n",append=TRUE);
        }    
} 
sink();
