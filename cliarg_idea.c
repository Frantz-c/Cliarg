t = {
    "(int)",
    "(string)",
    "-r|--recursive",
    "(string)",
    "(int)",
    NULL
};

t[0] = (int);
t[1] = (string);
t[2] = -r;
t[3] = (string);
t[4] = (int);

coucou :: ac = 1

i = 0;
// Check first NOPREFIX arguments
while (t[i] && t[i]->type & NOPREFIX)
    i++;
if (i > 0)
{
    int j = 0;
    while (j < i)
    {
        if (j > ac)
        {
            set_error(CLI_TOFEW_ARG);
            return ; // no free
        }
        t[j]->value = dup(av[j]);
        checked[j] = 1;
        j++;
    }
}
// Check last NOPREFIX arguments
while (t[i] && !(t[i]->type & NOPREFIX))
    i++;
if (t[i])
{
    j = i;
    while (t[j]->type & NOPREFIX)
        j++;
    int nlast = j - i;
    j = ac - nlast;
    if (j < 0)
    {
        set_error(CLI_TOFEW_ARG);
        return ;
    }
    while (nlast)
    {
        if (j > -1 && !checked[j])
        {
            t[i]->value = dup(av[j]);
            checked[j] = 1;
            i++;
        }
        nlast--;
        j++;
    }
}
