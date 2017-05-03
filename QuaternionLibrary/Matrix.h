#pragma once
namespace QuaternionLibrary
{
	template <typename numtype> struct Matrix4x4;

#pragma region HelperStructs
	template <typename numtype> struct Row
	{
		union
		{
			numtype Array[4];
			struct
			{
				numtype X;
				numtype Y;
				numtype Z;
				numtype W;
			};
		};
		inline void ApplyToMatrix(Matrix4x4<numtype>& Matrix, int RowNumber)
		{
			for (size_t i = 0; i < 4; i++)
			{
				Matrix.Array2D[RowNumber][i] = Array[i];
			}
		}
	};
	template <typename numtype> struct Column
	{
		union
		{
			numtype Array[4];
			struct
			{
				numtype X;
				numtype Y;
				numtype Z;
				numtype W;
			};
		};
		inline void ApplyToMatrix(Matrix4x4<numtype>& Matrix, int ColumnNumber)
		{
			for (size_t i = 0; i < 4; i++)
			{
				Matrix.Array2D[i][ColumnNumber] = Array[i];
			}
		}
		inline void ReadFromMatrix(Matrix4x4<numtype> const & Matrix, int ColumnNumber)
		{
			for (size_t i = 0; i < 4; i++)
			{
				Array[i] = Matrix.Array2D[i][ColumnNumber];
			}
		}
	};

	template <typename numtype> union RowColumn
	{
		Row<numtype> mRow;
		Column<numtype> mColumn;
	};

	template <typename numtype> numtype operator*(Row<numtype> const & _Row, Column<numtype> const & _Column)
	{
		numtype out;

		out = 0;

		for (size_t i = 0; i < 4; i++)
		{
			out += _Row.Array[i] * _Column.Array[i];
		}

		return out;
	}

#pragma endregion
	template <typename numtype> struct Matrix4x4
	{

		union
		{
			numtype Array[16];
			numtype Array2D[4][4];
			struct
			{
				numtype ArrayX[4];
				numtype ArrayY[4];
				numtype ArrayZ[4];
				numtype ArrayW[4];
			};
			struct
			{
				Row<numtype> RowX;
				Row<numtype> RowY;
				Row<numtype> RowZ;
				Row<numtype> RowW;
			};
			struct
			{
				numtype _0_0;
				numtype _1_0;
				numtype _2_0;
				numtype _3_0;

				numtype _0_1;
				numtype _1_1;
				numtype _2_1;
				numtype _3_1;

				numtype _0_2;
				numtype _1_2;
				numtype _2_2;
				numtype _3_2;

				numtype _0_3;
				numtype _1_3;
				numtype _2_3;
				numtype _3_3;
			};
		};

		Column<numtype> GetXColumn() const
		{
			Column<numtype> Out;
			Out.ReadFromMatrix(*this, 0);
			return Out;
		}

		Column<numtype> GetYColumn() const
		{
			Column<numtype> Out;
			Out.ReadFromMatrix(*this, 1);
			return Out;
		}

		Column<numtype> GetZColumn() const
		{
			Column<numtype> Out;
			Out.ReadFromMatrix(*this, 2);
			return Out;
		}

		Column<numtype> GetWColumn() const
		{
			Column<numtype> Out;
			Out.ReadFromMatrix(*this, 3);
			return Out;
		}

		Matrix4x4& Transpose()
		{
			Matrix4x4 Out;

			RowColumn<numtype> A;

			RowColumn<numtype> B;

			RowColumn<numtype> C;

			RowColumn<numtype> D;

			A.mRow = RowX;
			B.mRow = RowY;
			C.mRow = RowZ;
			D.mRow = RowW;

			A.mColumn.ApplyToMatrix(*this, 0);
			B.mColumn.ApplyToMatrix(*this, 1);
			C.mColumn.ApplyToMatrix(*this, 2);
			D.mColumn.ApplyToMatrix(*this, 3);
			return *this;
		}

		Matrix4x4 operator*(Matrix4x4 const & Other)
		{
			Matrix4x4 Out;

			//Get Other as columns, since we can't use it as rows and doing it repeatedly will waste a lot of time if it's not optimized out.

			Column<numtype> ColumnX = Other.GetXColumn();
			Column<numtype> ColumnY = Other.GetYColumn();
			Column<numtype> ColumnZ = Other.GetZColumn();
			Column<numtype> ColumnW = Other.GetWColumn();

			Out.RowX.X = RowX * ColumnX;
			Out.RowX.Y = RowX * ColumnY;
			Out.RowX.Z = RowX * ColumnZ;
			Out.RowX.W = RowX * ColumnW;

			Out.RowY.X = RowY * ColumnX;
			Out.RowY.Y = RowY * ColumnY;
			Out.RowY.Z = RowY * ColumnZ;
			Out.RowY.W = RowY * ColumnW;

			Out.RowZ.X = RowZ * ColumnX;
			Out.RowZ.Y = RowZ * ColumnY;
			Out.RowZ.Z = RowZ * ColumnZ;
			Out.RowZ.W = RowZ * ColumnW;

			Out.RowW.X = RowW * ColumnX;
			Out.RowW.Y = RowW * ColumnY;
			Out.RowW.Z = RowW * ColumnZ;
			Out.RowW.W = RowW * ColumnW;

			return Out;

		}

	};
	typedef Matrix4x4<float> Matrix4x4f;
	typedef Matrix4x4<double> Matrix4x4d;
}