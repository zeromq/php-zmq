# Define version and release number
%define version @PACKAGE_VERSION@
%define release 1

Name:          php-zeromq
Version:       %{version}
Release:       %{release}%{?dist}
Packager:      Mikko Koppanen <mkoppanen@php.net>
Summary:       PHP 0MQ extension
License:       BSD License
Group:         Web/Applications
URL:           http://github.com/mkoppanen/php-zeromq
Source:        zeromq-%{version}.tgz
Prefix:        %{_prefix}
Buildroot:     %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: php-devel, make, gcc, /usr/bin/phpize, zeromq-devel >= 2.0.7
Requires:      zeromq >= 2.0.7

%description
PHP extension for 0MQ messaging system

%prep
%setup -q -n zeromq-%{version}

%build
/usr/bin/phpize && %configure && %{__make} %{?_smp_mflags}

# Clean the buildroot so that it does not contain any stuff from previous builds
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}

# Install the extension
%{__make} install INSTALL_ROOT=%{buildroot}

# Create the ini location
%{__mkdir} -p %{buildroot}/etc/php.d

# Preliminary extension ini
echo "extension=zeromq.so" > %{buildroot}/%{_sysconfdir}/php.d/zeromq.ini

%clean
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}

%files
%{_libdir}/php/modules/zeromq.so
%{_sysconfdir}/php.d/zeromq.ini

%changelog
* Thu Apr 8 2010 Mikko Koppanen <mkoppanen@php.net>
 - Initial spec file
