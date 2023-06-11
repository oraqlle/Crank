// -*- C++ -*- Header compatibility <crank.hxx>

/// \brief
///
/// Author: Tyler Swann (tyler.swann05@gmail.com)
///
/// Header Version: v0.1.0
///
/// Date: 02-01-2023
///
/// License: MIT
///
/// Copyright: Copyright (c) 2022-2023
/// \file crank.hxx

#ifndef CRANK_HXX
#define CRANK_HXX

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_CRANK
#define CRANK_PUBLIC __declspec(dllexport)
#else
#define CRANK_PUBLIC __declspec(dllimport)
#endif
#else
#ifdef BUILDING_CRANK
#define CRANK_PUBLIC __attribute__((visibility("default")))
#else
#define CRANK_PUBLIC
#endif
#endif

#include <engine.hxx>
#include <state_interface.hxx>

#endif /// CRANK_HXX
