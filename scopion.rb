# Documentation: https://docs.brew.sh/Formula-Cookbook.html
#                http://www.rubydoc.info/github/Homebrew/brew/master/Formula
# PLEASE REMOVE ALL GENERATED COMMENTS BEFORE SUBMITTING YOUR PULL REQUEST!

class Scopion < Formula
	desc "a statically-typed functional programming language with powerful objective syntax"
	homepage "https://scopion.coord-e.com/"
	url "https://github/coord-e/scopion.git"
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
    # ENV.deparallelize  # if your formula fails when building in parallel
  
		preCheck # check architecture,OS,macOS version

		bin.install "bin/scopc" # Install scopc executable
		lib.install "lib/libscopion.dylib" # Install libraries into #{HOMEBREW_PREFIX}/lib
		prefix.install Dir["include"], Dir["etc"]
		ohai "Do update_dyld_shared_cache in order to include path for libscopion.dylib" # ohai --> Display general info
		system "sudo" "update_dyld_shared_cache"
	  end

	test do
		ohai "Test compiling hello world.."

		system "scopc", "hello.scc", "-o", "hello" # Compile test
		system "./hello"

	end
end
