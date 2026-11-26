#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <cerrno>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;

#ifndef _WIN32
//class TerminalMode {
public:
    TerminalMode() {
        if (!isatty(STDIN_FILENO) || tcgetattr(STDIN_FILENO, &original_) == -1) {
            throw runtime_error("Snake requires an interactive terminal.");
        }

        termios raw = original_;
        raw.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) {
            throw runtime_error("Unable to configure terminal input.");
        }
    }

    ~TerminalMode() {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_);
    }

private:
    termios original_{};
};
#endif

int readKeyIfAvailable() {
#ifdef _WIN32
    return _kbhit() ? _getch() : -1;
#else
    fd_set input;
    FD_ZERO(&input);
    FD_SET(STDIN_FILENO, &input);
    timeval timeout{};
    const int ready = select(STDIN_FILENO + 1, &input, nullptr, nullptr, &timeout);
    if (ready == -1) {
        if (errno == EINTR) return -1;
        throw runtime_error("Unable to read terminal input.");
    }
    if (ready == 0) return -1;

    unsigned char key;
    const ssize_t count = read(STDIN_FILENO, &key, 1);
    if (count == -1 && errno != EINTR) {
        throw runtime_error("Unable to read terminal input.");
    }
    return count == 1 ? key : -1;
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

// Huong di chuyen cua ran:
//   0 = phai (d), 1 = xuong (x), 2 = trai (a), 3 = len (w)

// Dua con tro console den vi tri (column, line)
void gotoxy( int column, int line );
struct Point{
    int x,y;
};
// CONRAN: con ran. A[0] la dau, A[1..DoDai-1] la than.
class CONRAN{
public:
    Point A[100];  // toa do cac dot cua ran
    int DoDai;     // so dot hien tai
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 9; A[1].y = 10;
        A[2].x = 8; A[2].y = 10;
    }
    // Ve ran len man hinh console
    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"X";
        }
    }
    // Di chuyen ran 1 o theo Huong: than doi theo dot phia truoc, dau di tiep
    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }
};

int main()
{
#ifndef _WIN32
    try {
        TerminalMode terminalMode;
#endif
    CONRAN r;
    int Huong = 0;

    while (true){
        const int key = readKeyIfAvailable();
        if (key == 'q' || key == 'Q') break;
        // Khong cho quay dau 180 do (tu can vao than)
        if (key == 'a' && Huong != 0) Huong = 2;
        if (key == 'w' && Huong != 1) Huong = 3;
        if (key == 'd' && Huong != 2) Huong = 0;
        if (key == 'x' && Huong != 3) Huong = 1;

        clearScreen();
        r.Ve();
        cout.flush();
        r.DiChuyen(Huong);
        this_thread::sleep_for(chrono::milliseconds(300));
    }
#ifndef _WIN32
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
#endif

    return 0;
}


void gotoxy( int column, int line )
  {
#ifdef _WIN32
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
#else
  cout << "\033[" << line + 1 << ";" << column + 1 << "H";
#endif
  }
