/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "DNA_node_types.h"

#include "MEM_guardedalloc.h"

#include "node_geometry_util.hh"

namespace blender::nodes::node_geo_set_dmatrix_entry_cc {

static void node_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::DMatrix>("DMatrix")
      .description("Input DMatrix");
  b.add_input<decl::Int>("Row")
      .default_value(0)
      .min(0)
      .description("Row index (0-based)");
  b.add_input<decl::Int>("Column")
      .default_value(0)
      .min(0)
      .description("Column index (0-based)");
  b.add_input<decl::Float>("Value")
      .default_value(0.0f)
      .description("Value to set at the specified row and column");
  b.add_output<decl::DMatrix>("DMatrix")
      .description("Output DMatrix with modified entry");
}

static void node_geo_exec(GeoNodeExecParams params)
{
  /* Extract inputs */
  /* TODO: Extract DMatrix input when SocketValueVariant supports it */
  const int row = params.extract_input<int>("Row");
  const int column = params.extract_input<int>("Column");
  const float value = params.extract_input<float>("Value");
  
  (void)row;
  (void)column;
  (void)value;
  
  /* For now, we create a placeholder output. 
   * Proper DMatrix support in SocketValueVariant needs to be added separately. */
  /* TODO: Add proper DMatrix support to SocketValueVariant */
  /* TODO: Implement matrix entry setting logic:
   * 1. Extract input DMatrix
   * 2. Validate row/column indices are within bounds
   * 3. Create a copy of the matrix
   * 4. Set the value at matrix[row * cols + column] = value
   * 5. Output the modified matrix
   */
  params.set_output("DMatrix", 0.0f);
}

static void node_register()
{
  static blender::bke::bNodeType ntype;

  geo_node_type_base(&ntype, "GeometryNodeSetDMatrixEntry", GEO_NODE_SET_DMATRIX_ENTRY);
  ntype.ui_name = "Set DMatrix Entry";
  ntype.ui_description = "Set a value at a specific row and column in a DMatrix";
  ntype.enum_name_legacy = "SET_DMATRIX_ENTRY";
  ntype.nclass = NODE_CLASS_GEOMETRY;
  ntype.geometry_node_execute = node_geo_exec;
  ntype.declare = node_declare;
  blender::bke::node_register_type(ntype);
}
NOD_REGISTER_NODE(node_register)

}  // namespace blender::nodes::node_geo_set_dmatrix_entry_cc

