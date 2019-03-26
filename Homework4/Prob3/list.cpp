void listAll(const MenuItem* m, string path) // two-parameter overload
{
    //If m is a Compound Menu
    if(m->menuItems() != nullptr && m->menuItems()->size() != 0)
    {
        vector<MenuItem*>::const_iterator it;
        for(it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
        {
            cout << path << (*it)->name() << endl;
            listAll(*it, path + (*it)->name() + "/");
        }
    }
    else
        return;
    
}
