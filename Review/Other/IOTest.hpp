int read() {
    int res = 0;
    char c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void writeImpl(int x) {
    if(x >= 10)
        writeImpl(x / 10);
    IO::putc('0' + x % 10);
}
void write(int x) {
    writeImpl(x);
    IO::putc('\n');
}
int main() {
    IO::init();
    int n = read();
    write(n);
    while(n--)
        write(read());
    IO::uninit();
    return 0;
}
