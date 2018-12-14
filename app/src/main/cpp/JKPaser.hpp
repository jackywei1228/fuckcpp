
class JKPaser
{
public:
    JKPaser(std::string name);
    int addListener();
protected:
private:
};

class JKPaserListener {
    public:
        virtual int onRecive() = 0;
};