/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "hexRef.H"

#include "polyMesh.H"
#include "autoPtr.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::hexRef> Foam::hexRef::New
(
    const polyMesh& mesh,
    const bool readHistory
)
{
    word hexRefTypeName;

    // Infer the type of hexRef we need to use from the number of dimensions in
    // the polymesh
    // nSolutionD == 3 && nGeometricD == 3: 3D mesh => hexRef3D
    // nSolutionD == 3 && nGeometricD == 2: axisymmetric mesh => hexRef4Axi
    // nSolutionD == 2 && nGeometricD == 2: 2D mesh => hexRef4

    label nSoluD(mesh.nSolutionD());
    label nGeomD(mesh.nGeometricD());

    if (nSoluD == 3 && nGeomD == 3)
    {
        hexRefTypeName = "hexRef3D";
    }
    else if (nSoluD == 3 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4Axi";
    }
    else if (nSoluD == 2 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4";
    }

#if OPENFOAM >= 2206
    auto hexRefCtor = meshConstructorTable(hexRefTypeName);

    if (!hexRefCtor)
#else
    meshConstructorTable::iterator hexRefIter =
        meshConstructorTablePtr_->find(hexRefTypeName);

    if (hexRefIter == meshConstructorTablePtr_->end())
#endif
    {
        FatalErrorInFunction
            << "Unsupported mesh number of dimensions for hex refinement" << nl
            << "nSolutionD: " << nSoluD << ", nGeometricD: " << nGeomD << nl
            << "Only 3D, 2D and 2D axisymmetric mesh refinements are supported"
            << exit(FatalError);
    }

    return autoPtr<hexRef>
    (
#if OPENFOAM >= 2206
        hexRefCtor(mesh, readHistory)
#else
        hexRefIter()(mesh, readHistory)
#endif
    );
}

Foam::autoPtr<Foam::hexRef> Foam::hexRef::New
(
    const polyMesh& mesh,
    const labelList& cellLevel,
    const labelList& pointLevel,
    const refinementHistoryMultiDim& history,
    const scalar level0Edge
)
{
    word hexRefTypeName;

    // Infer the type of hexRef we need to use from the number of dimensions in
    // the polymesh
    // nSolutionD == 3 && nGeometricD == 3: 3D mesh => hexRef3D
    // nSolutionD == 3 && nGeometricD == 2: axisymmetric mesh => hexRef4Axi
    // nSolutionD == 2 && nGeometricD == 2: 2D mesh => hexRef4

    label nSoluD(mesh.nSolutionD());
    label nGeomD(mesh.nGeometricD());

    if (nSoluD == 3 && nGeomD == 3)
    {
        hexRefTypeName = "hexRef3D";
    }
    else if (nSoluD == 3 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4Axi";
    }
    else if (nSoluD == 2 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4";
    }

#if OPENFOAM >= 2206
    auto hexRefCtor = levelsHistConstructorTable(hexRefTypeName);

    if (!hexRefCtor)
#else
    levelsHistConstructorTable::iterator hexRefIter =
        levelsHistConstructorTablePtr_->find(hexRefTypeName);

    if (hexRefIter == levelsHistConstructorTablePtr_->end())
#endif
    {
        FatalErrorInFunction
            << "Unsupported mesh number of dimensions for hex refinement" << nl
            << "nSolutionD: " << nSoluD << ", nGeometricD: " << nGeomD << nl
            << "Only 3D, 2D and 2D axisymmetric mesh refinements are supported"
            << exit(FatalError);
    }

    return autoPtr<hexRef>
    (
#if OPENFOAM >= 2206
        hexRefCtor(mesh, cellLevel, pointLevel, history, level0Edge)
#else
        hexRefIter()(mesh, cellLevel, pointLevel, history, level0Edge)
#endif
    );
}

Foam::autoPtr<Foam::hexRef> Foam::hexRef::New
(
    const polyMesh& mesh,
    const labelList& cellLevel,
    const labelList& pointLevel,
    const scalar level0Edge
)
{
    word hexRefTypeName;

    // Infer the type of hexRef we need to use from the number of dimensions in
    // the polymesh
    // nSolutionD == 3 && nGeometricD == 3: 3D mesh => hexRef3D
    // nSolutionD == 3 && nGeometricD == 2: axisymmetric mesh => hexRef4Axi
    // nSolutionD == 2 && nGeometricD == 2: 2D mesh => hexRef4

    label nSoluD(mesh.nSolutionD());
    label nGeomD(mesh.nGeometricD());

    if (nSoluD == 3 && nGeomD == 3)
    {
        hexRefTypeName = "hexRef3D";
    }
    else if (nSoluD == 3 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4Axi";
    }
    else if (nSoluD == 2 && nGeomD == 2)
    {
        hexRefTypeName = "hexRef4";
    }

#if OPENFOAM >= 2206
    auto hexRefCtor = levelsConstructorTable(hexRefTypeName);

    if (!hexRefCtor)
#else
    levelsConstructorTable::iterator hexRefIter =
        levelsConstructorTablePtr_->find(hexRefTypeName);

    if (hexRefIter == levelsConstructorTablePtr_->end())
#endif
    {
        FatalErrorInFunction
            << "Unsupported mesh number of dimensions for hex refinement" << nl
            << "nSolutionD: " << nSoluD << ", nGeometricD: " << nGeomD << nl
            << "Only 3D, 2D and 2D axisymmetric mesh refinements are supported"
            << exit(FatalError);
    }

    return autoPtr<hexRef>
    (
#if OPENFOAM >= 2206
        hexRefCtor(mesh, cellLevel, pointLevel, level0Edge)
#else
        hexRefIter()(mesh, cellLevel, pointLevel, level0Edge)
#endif
    );
}

// ************************************************************************* //
