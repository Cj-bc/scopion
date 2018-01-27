class Scopion < Formula
	desc "a statically-typed functional programming language with powerful objective syntax"
	homepage "https://scopion.coord-e.com/"
	url "https://github.com/Cj-bc/homebrew-scopion.git"
	version "0.0.3.1"
	sha256 ""

	SupportedOSLeast = "10.12"

	depends_on "cmake" => :build
	depends_on "wget" 
	depends_on "unzip"
	depends_on "ctags"
	depends_on "boost"
	depends_on "llvm"
	depends_on "bdw-gc"


	def preCheck
		# test architecture. x86_64 is needed
		if `uname -m` != "x86_64" then
			odie "Architecture x86_64 is needed.Yours isn't it." # odie --> display error messages and exist.
		end

		# I don't treat with Linux yet. I'll do it later,sorry :(
		if OS.linux? then
			odie "Linuxbrew isn't supported yet. We're commiting now,sorry ;("
		end

		# Check wether used mac version is supported
		if `sw_vers -productVersion` <= SupportedOSLeast then
			odie "Unsaopported macOS version.You need #{SupportedOSLeast} or later"
		end
	end


	def install
  
		preCheck # check architecture,OS,macOS version

		system "mkdir", "build", "&&", "cd", "$_"
		cmake .. -DCMAKE_BUILD_TYPE=Release -DFORMAT_BEFORE_BUILD=OFF
		make -j"$(nproc)" # build
		sudo make install # install
	end

	test do
		ohai "Test compiling hello world.."

		system "scopc", "hello.scc", "-o", "hello" # Compile test
		system "./hello"

	end
end
