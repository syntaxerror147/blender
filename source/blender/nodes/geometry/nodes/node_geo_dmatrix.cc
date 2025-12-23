/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "DNA_node_types.h"

#include "MEM_guardedalloc.h"

#include "node_geometry_util.hh"

namespace blender::nodes::node_geo_dmatrix_cc {

static void node_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::Int>("Rows")
      .default_value(1)
      .min(1)
      .description("Number of rows");
  b.add_input<decl::Int>("Columns")
      .default_value(1)
      .min(1)
      .description("Number of columns");
  b.add_output<decl::DMatrix>("DMatrix")
      .description("Output DMatrix");
}
 
static void node_geo_exec(GeoNodeExecParams params)
{
  /* Extract inputs */
  const int rows = params.extract_input<int>("Rows");
  const int columns = params.extract_input<int>("Columns");
  (void)rows;
  (void)columns;
  
  /* For now, we create a placeholder output. 
   * Proper DMatrix support in SocketValueVariant needs to be added separately. */
  /* TODO: Add proper DMatrix support to SocketValueVariant */
  params.set_output("DMatrix", 0.0f);
}

static void node_register()
{
  static blender::bke::bNodeType ntype;

  geo_node_type_base(&ntype, "GeometryNodeDMatrix", GEO_NODE_DMATRIX);
  ntype.ui_name = "DMatrix";
  ntype.ui_description = "DMatrix node";
  ntype.enum_name_legacy = "DMATRIX";
  ntype.nclass = NODE_CLASS_GEOMETRY;
  ntype.geometry_node_execute = node_geo_exec;
  ntype.declare = node_declare;
  blender::bke::node_register_type(ntype);
}
NOD_REGISTER_NODE(node_register)

}  // namespace blender::nodes::node_geo_dmatrix_cc