How to use cpp client lib
--------------------------------------------

## Option One: Get package from github

### Down package

```bash
wget https://github.com/vesoft-inc/nebula-cpp/releases/download/$release-version/nebula-graph-client-$version.$system.x86_64.rpm
```

### Install lib to local

- Centos

```bash
bash> sudo rpm -ivh nebula-graph-client-$version.$system.x86_64.rpm
```

- Ubuntu

```bash
bash> sudo dpkg -i nebula-graph-client-$version.$system.amd64.deb
```

### Update the dynamic library cache

```bash
bash> ldconfig
```

## Option Two: Build by source code

### clone nebula src

```
git clone https://github.com/vesoft-inc/nebula-clients.git
```

### build

```bash
bash> cd nebula-clients/cpp && mkdir build && cd build
bash> cmake ..
bash> make && sudo make install
```

If your g++ can't support c++11, you need to configure building by cmake like this

```bash
bash> cmake -DDISABLE_CXX11_ABI=ON ..
```


after finish building, cp the lib and include files to your dir

## How to use in your code

- Step 1: init arvs(a process can only call once)
- Step 2: init connection pool, the default connections is 10, timeout is 1000 ms (a process can only call once),
- Step 3: get a session
- Step 4: execute your statements
- Step 5: release session

Please refer to the [sample code](examples/SessionExample.cpp) on detail usage.

build and run example code
If your g++ version is more than 5.0

```bash
LIBRARY_PATH=${Your Installed Library Folder}:$LIBRARY_PATH g++ -std=c++11 SessionExample.cpp -I${Your Installed Include folder} -lnebula_graph_client -o session_example
```

If your g++ version is less than 5.0

```bash
LIBRARY_PATH=${Your Installed Library Folder}:$LIBRARY_PATH g++ -std=c++11 SessionExample.cpp -I${Your Installed Include folder} -lnebula_graph_client -o session_example -D _GLIBCXX_USE_CXX11_ABI=0
```

Run the example (require a available nebula graph 2.0 server in '127.0.0.1:3699')

```bash
LD_LIBRARY_PATH=${Your Installed Library Folder}:$LD_LIBRARY_PATH ./session_example
```

Or if you're familiar to cmake you could try build and run by cmake directly.
