function strcat(x,y)
{
    x=x+y;
    return x;
}

function strcpy(x,y)
{
    x=y;
    return x;
}

function cntchstr(x,y)
{
    var res=0;
    for(var i=0;i<y.length;i++)
    {
        if(y[i]==x)
        {
            res++;
        }
    }
    return res;
}

function strtoint(x)
{
    return Number(x);
}