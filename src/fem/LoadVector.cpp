#include "pba/fem/LoadVector.h"

#include "pba/common/ConstexprFor.h"
#include "pba/fem/Mesh.h"
#include "pba/fem/Tetrahedron.h"

#include <doctest/doctest.h>

TEST_CASE("[fem] LoadVector")
{
    using namespace pba;

    // Cube tetrahedral mesh
    MatrixX V(3, 8);
    IndexMatrixX C(4, 5);
    // clang-format off
    V << 0., 1., 0., 1., 0., 1., 0., 1.,
            0., 0., 1., 1., 0., 0., 1., 1.,
            0., 0., 0., 0., 1., 1., 1., 1.;
    C << 0, 3, 5, 6, 0,
            1, 2, 4, 7, 5,
            3, 0, 6, 5, 3,
            5, 6, 0, 3, 6;
    // clang-format on

    common::ForRange<1, 3>([&]<auto kOrder>() {
        common::ForRange<1, 4>([&]<auto OutDims> {
            using Element        = fem::Tetrahedron<kOrder>;
            auto constexpr kDims = 3;
            using Mesh           = fem::Mesh<Element, kDims>;
            Mesh mesh(V, C);
            auto const N = mesh.X.cols();
            auto const n = N * OutDims;

            using LoadVector = fem::LoadVector<Mesh, OutDims>;
            LoadVector loadVector(mesh, Vector<OutDims>::Ones());

            VectorX const f = loadVector.ToVector();
            CHECK_EQ(f.rows(), n);
        });
    });
}